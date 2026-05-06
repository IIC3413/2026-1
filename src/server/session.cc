#include "session.h"

#include <iostream>
#include <cctype>

#include "query/optimizer/optimizer.h"
#include "query/parser/parser.h"
#include "system/system.h"

using namespace boost;

Session::Session(boost::asio::ip::tcp::socket socket)
    : socket(std::move(socket)) {}

void Session::read_header() {
  asio::async_read(
      socket, request_buffer.prepare(sizeof(uint32_t)), boost::asio::transfer_all(),
      [self = this->shared_from_this()](const boost::system::error_code& ec, std::size_t) {
        if (ec) {
          if (ec == boost::asio::error::eof) {
            std::cout << "Client disconnected" << std::endl;
            self->handle_abort();
          } else {
            std::cout << "Could not read the query header from client: " << ec.message() << std::endl;
          }
          return;
        }
        self->request_buffer.commit(sizeof(uint32_t));

        uint32_t len = ntohl(*static_cast<const uint32_t*>(self->request_buffer.data().data()));

        self->request_buffer.consume(sizeof(uint32_t));
        self->read_query(len);
      }
  );
}

void Session::read_query(uint32_t msg_size) {
  query.resize(msg_size);
  asio::async_read(
      socket, boost::asio::buffer(query.data(), msg_size), boost::asio::transfer_all(),
      [self = this->shared_from_this()](const boost::system::error_code& ec, std::size_t) {
        if (ec) {
          if (ec == boost::asio::error::eof) {
            std::cout << "Client disconnected" << std::endl;
            self->handle_abort();
          } else {
            std::cout << "Could not read the query from client: " << ec.message() << std::endl;
          }
          return;
        }
        self->process_query();
      }
  );
}

void Session::process_query() {
  std::cout << "[Query] " << query << std::endl;

  std::string response;
  try {
    response = run_query();
  } catch (LockException& e) {
    handle_system_abort();
    response = "Transaction aborted due to lock timeout:\n";
    response += e.what();
  } catch (AbortException& e) {
    handle_system_abort();
    response = "Transaction aborted:\n";
    response += e.what();
  } catch (const std::exception& e) {
    response = "Error running the query:\n";
    response += e.what();
  } catch (...) {
    response = "Unknown error running the query";
  }

  uint32_t resp_len = htonl(static_cast<uint32_t>(response.size()));

  std::vector<boost::asio::const_buffer> buffers;
  buffers.push_back(boost::asio::buffer(&resp_len, sizeof(resp_len)));
  buffers.push_back(boost::asio::buffer(response));

  boost::system::error_code ec;
  boost::asio::write(socket, buffers, ec);

  if (ec) {
    if (ec == boost::asio::error::eof) {
      std::cout << "Client disconnected" << std::endl;
      handle_abort();
    } else {
      std::cerr << "error writing response: " << ec.what() << std::endl;
    }
    return;
  }

  // Start again
  read_header();
}

std::string Session::execute_query(const std::string& query, TxID tx_id, bool commit_at_end) {
  auto logical_plan = Parser::parse(query, false, tx_id);
  Optimizer optimizer(tx_id);
  PhysicalPlan plan = optimizer.create_physical_plan(std::move(logical_plan));

  if (std::holds_alternative<std::unique_ptr<QueryAction>>(plan)) {
    auto action = std::move(std::get<std::unique_ptr<QueryAction>>(plan));
    action->execute();
    if (commit_at_end) {
      transaction_mgr.commit_transaction(tx_id);
    }
    return "Action executed successfully in TxID: " + std::to_string(tx_id);
  } else if (std::holds_alternative<std::unique_ptr<QueryIter>>(plan)) {
    auto query_iter = std::move(std::get<std::unique_ptr<QueryIter>>(plan));
    std::stringstream result;
    char sep[2] = {'\0', '\0'};
    query_iter->begin();

    // print header
    auto cols = query_iter->get_columns();
    bool not_same_alias = false;
    for (size_t i = 1; i < cols.size(); i++) {
      if (cols[i].alias != cols[i - 1].alias) {
        not_same_alias = true;
        break;
      }
    }

    for (auto& col : cols) {
      result << sep;
      if (not_same_alias) {
        result << col.alias;
        result << '.';
      }
      result << col.info.name;
      sep[0] = ',';
    }
    result << "\n";

    int total_results = 0;
    for (auto record = query_iter->next(); !record.invalid(); record = query_iter->next()) {
      total_results++;
      result << record.to_string() << "\n";
    }

    if (commit_at_end) {
      transaction_mgr.commit_transaction(tx_id);
    }
    return "Query executed successfully with " + std::to_string(total_results) +
           " results in TxID: " + std::to_string(tx_id) + "\n" + result.str();
  }
  return "Unhandled Query Type";
}

bool my_compare(const std::string& s, const std::string& target) {
  if (s.size() < target.size()) return false;
  for (size_t i = 0; i < target.size(); i++) {
    if (std::tolower(s[i]) != std::tolower(target[i]))  {
      return false;
    }
  }
  return true;
}

std::string Session::run_query() {
  if (state == 0) {
    //if (query.compare(0, 17, "BEGIN TRANSACTION") == 0) {
    if (my_compare(query, "BEGIN TRANSACTION")) {
      state = 1;
      // TODO: Add other isolation levels
      tx_id = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED).get_id();
      return "Transaction started with ID: " + std::to_string(tx_id);
    }
    if (my_compare(query, "COMMIT")) {
      return "There is no active transaction to commit";
    }
    if (my_compare(query, "ABORT")) {
      return "There is no active transaction to abort";
    }
    if (my_compare(query, "VACUUM")) {
      catalog.vacuum(0);
      return "Vacuum completed successfully in transaction ID: " + std::to_string(tx_id);
    }
    tx_id = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED).get_id();
    return execute_query(query, tx_id, true);
  } else if (state == 1) {
    if (my_compare(query, "BEGIN TRANSACTION")) {
      return "Already in a transaction with ID: " + std::to_string(tx_id);
    }
    if (my_compare(query, "COMMIT")) {
      transaction_mgr.commit_transaction(tx_id);
      state = 0;
      return "Transaction committed successfully";
    }
    if (my_compare(query, "ABORT")) {
      transaction_mgr.abort_transaction(tx_id);
      state = 0;
      return "Transaction aborted successfully";
    }
    if (my_compare(query, "VACUUM")) {
      catalog.vacuum(tx_id);
      return "Vacuum completed successfully in transaction ID: " + std::to_string(tx_id);
    }

    return execute_query(query, tx_id, false);
  }
  return "Unknown command : " + query;
}

void Session::run() {
  read_header();
}

// Abort it's called when the transaction is aborted internally (lock timeout, deadlock, etc.)
void Session::handle_system_abort() {
  if (state == 1) {
    state = 0;
  }
}

// Handle abort when client disconnects in the middle of a transaction
void Session::handle_abort() {
  if (state == 1) {
    try {
      transaction_mgr.abort_transaction(tx_id);
      state = 0;
    } catch (std::runtime_error& e) { // Transaction already aborted, just set the state to 0
      state = 0;
    }
  } else {
    try {
      transaction_mgr.abort_transaction(tx_id);
    } catch (std::runtime_error& e) { // Transaction already aborted, just set the state to 0
      // Do nothing
    }
  }
}

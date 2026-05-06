#pragma once

#include <boost/asio.hpp>

#include "system/tx_id.h"

class Session : public std::enable_shared_from_this<Session> {
public:
  Session(boost::asio::ip::tcp::socket socket);

  void run();

  void read_header();

  void read_query(uint32_t msg_size);

  void process_query();

private:
  boost::asio::ip::tcp::socket socket;

  boost::asio::streambuf request_buffer;

  std::string query;

  int state = 0;

  TxID tx_id;

  std::string run_query();

  void handle_system_abort();

  void handle_abort();

  std::string execute_query(const std::string& query, TxID tx_id, bool commit_at_end);
};

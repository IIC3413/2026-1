#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "third_party/linenoise/linenoise.h"

using boost::asio::ip::tcp;

class DBMSClient {
public:
  DBMSClient(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
      : socket_(io_context) {
    tcp::resolver resolver(io_context);
    boost::asio::connect(socket_, resolver.resolve(host, port));
  }

  void send_query(const std::string& query) {
    // 1. Prepare Header (Length of string)
    uint32_t len = htonl(static_cast<uint32_t>(query.size()));

    // 2. Write Header + Body
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(&len, sizeof(len)));
    buffers.push_back(boost::asio::buffer(query));
    boost::asio::write(socket_, buffers);
  }

  std::string receive_response() {
    // 1. Read Header
    uint32_t len;
    boost::asio::read(socket_, boost::asio::buffer(&len, sizeof(len)));
    len = ntohl(len);

    // 2. Read Body
    std::vector<char> body(len);
    boost::asio::read(socket_, boost::asio::buffer(body));
    return std::string(body.begin(), body.end());
  }

private:
  tcp::socket socket_;
};

// 2. Optional: Add a simple completion callback
void completionHook(const char* buf, linenoiseCompletions* lc) {
  if (buf[0] == 'S' || buf[0] == 's') {
    linenoiseAddCompletion(lc, "SELECT ");
  } else if (buf[0] == 'I' || buf[0] == 'i') {
    linenoiseAddCompletion(lc, "INSERT INTO ");
  } else if (buf[0] == 'C' || buf[0] == 'c') {
    linenoiseAddCompletion(lc, "CREATE TABLE ");
  }
}

std::string_view rtrim(std::string_view sv) {
  while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.back()))) {
    sv.remove_suffix(1);
  }
  return sv;
}

int main(int argc, char** argv) {
  std::string port = (argc > 1) ? argv[1] : "4321";
  try {
    boost::asio::io_context io_context;
    DBMSClient client(io_context, "127.0.0.1", port);

    // std::string line;
    std::cout << "DBMS Prototype Shell\nPress Ctrl+D or type 'exit' to quit.\n";

    linenoiseSetMultiLine(1);
    linenoiseSetCompletionCallback(completionHook);
    linenoiseHistorySetMaxLen(100);

    const char* line_raw;
    const char* start_cmd = " > ";
    const char* continue_cmd = "...";

    const char* current_cmd = start_cmd;

    std::string query;
    while ((line_raw = linenoise(current_cmd)) != nullptr) {
      const std::string line(rtrim(std::string_view(line_raw)));

      if (line == "exit") {
        free((void*)line_raw);
        break;
      }

      if (!line.empty()) {
        // Add to history and send to server
        linenoiseHistoryAdd(line_raw);

        if (line.back() == ';') {
          query.append(line.begin(), line.end() - 1);
          client.send_query(query);
          query.clear();
          std::string response = client.receive_response();
          std::cout << '\n' << response << '\n' << std::endl;
          current_cmd = start_cmd;
        } else {
          query.append(line.begin(), line.end());
          query += '\n';
          current_cmd = continue_cmd;
        }
      }

      // Linenoise uses malloc, so we must free the buffer
      free((void*)line_raw);
    }
  } catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}

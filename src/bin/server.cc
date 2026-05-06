#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>

#include "server/listener.h"
#include "system/system.h"

using namespace boost;
using boost::asio::ip::tcp;

constexpr auto WORKER_THREADS = 8;
const auto default_db = "data/example_db";
const uint16_t default_port = 4321;

bool shutdown_server = false;

void signal_shutdown_server(int) {
  shutdown_server = true;
}

// Usage:
// server [db_folder?] [port?]
int main(int argc, char** argv) {
  std::string db_folder = default_db;
  uint16_t port = default_port;

  if (argc >= 2) {
      db_folder = argv[1];
  }
  if (argc >= 3) {
    try {
      port = std::stoi(argv[2]);
    } catch (...) {
      std::cerr << "Error parsing port '" << argv[2] <<"'\n";
      std::exit(EXIT_FAILURE);
    }
  }

  System system(db_folder);

  try {
    asio::io_context io_context;

    Listener listener(io_context, tcp::endpoint(tcp::v4(), port));

    std::signal(SIGTERM, &signal_shutdown_server);
    std::signal(SIGINT, &signal_shutdown_server);

    // Prevent io_context from finishing immediately while creating threads
    auto work_guard = asio::make_work_guard(io_context);

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> threads;
    threads.reserve(WORKER_THREADS);
    for (auto i = 0; i < WORKER_THREADS; ++i) {
      threads.emplace_back([&] { io_context.run(); });
    }

    listener.run();
    work_guard.reset();

    std::cout << "Server running on port " << port << std::endl;
    std::cout << "To terminate the server, press Ctrl+C" << std::endl;

    while (!shutdown_server) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    io_context.stop();

    // Wait for all threads in the thread pool to exit
    for (auto& thread : threads) {
      thread.join();
    }

  } catch (const std::exception& e) {
    std::cerr << "Server error: " << e.what() << std::endl;
  }

  std::cout << "\nServer terminated" << std::endl;

  return 0;
}

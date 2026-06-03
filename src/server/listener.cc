#include "listener.h"
#include "server/session.h"

#include <boost/asio/strand.hpp>
#include <iostream>

using namespace boost;

Listener::Listener(asio::io_context& io_context, asio::ip::tcp::endpoint endpoint)
    : io_context(io_context),
      acceptor(boost::asio::make_strand(io_context)),
      endpoint(endpoint) {
  boost::system::error_code ec;

  // Open the acceptor
  acceptor.open(endpoint.protocol(), ec);
  if (ec) {
    fail(ec, "open");
  }

  // Allow address reuse
  acceptor.set_option(asio::socket_base::reuse_address(true), ec);
  if (ec) {
    fail(ec, "set options");
  }

  // Bind to the server address
  acceptor.bind(endpoint, ec);
  if (ec) {
    fail(ec, "bind");
  }

  // Start listening for connections
  acceptor.listen(asio::socket_base::max_listen_connections, ec);
  if (ec) {
    fail(ec, "listen");
  }
}

void Listener::run() {
  acceptor.async_accept(
      boost::asio::make_strand(io_context),
      [&](const boost::system::error_code& ec, asio::ip::tcp::socket socket) {
        std::cout << "New client connected" << std::endl;
        if (!ec) {
          std::make_shared<Session>(std::move(socket))->run();
        }

        // Accept another connection
        run();
      }
  );
}

void Listener::fail(const boost::system::error_code& ec, char const* what) const {
  if (ec == boost::asio::error::address_in_use) {
    std::cout << "Port " << endpoint.port() << " already in use, try using a different port" << std::endl;
    std::exit(EXIT_FAILURE);
  } else {
    std::cout << "Listener error while trying to " << what << ": " << ec.message() << std::endl;
  }
}

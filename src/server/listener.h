#pragma once

#include <boost/asio.hpp>

class Listener {
public:
  boost::asio::io_context& io_context;
  boost::asio::ip::tcp::acceptor acceptor;
  boost::asio::ip::tcp::endpoint endpoint;

  explicit Listener(boost::asio::io_context& io_context, boost::asio::ip::tcp::endpoint endpoint);

  void run();

  void session(boost::asio::ip::tcp::socket socket);

private:
  inline void fail(const boost::system::error_code& ec, char const* what) const;
};

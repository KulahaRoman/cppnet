#pragma once
#include <cppstreams/socketstreams/socketstream.h>

#include <boost/asio.hpp>

#include "acceptor.h"
#include "unsecuretcpconnection.h"

class UnsecureTcpAcceptor : public Acceptor {
 public:
  UnsecureTcpAcceptor(const std::shared_ptr<boost::asio::io_context>& context,
                      const boost::asio::ip::tcp::endpoint& endpoint);
  ~UnsecureTcpAcceptor();

  std::shared_ptr<Connection> Accept() override;

  void Accept(
      const std::function<void(const std::shared_ptr<Connection>&)>& onSuccess,
      const std::function<void(const std::exception&)>& onFailure) override;

 private:
  boost::asio::ip::tcp::acceptor acceptor;
};

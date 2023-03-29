#pragma once
#include <cppstreams/socketstreams/socketstream.h>

#include <boost/asio.hpp>

#include "connector.h"
#include "unsecuretcpconnection.h"

class UnsecureTcpConnector : public Connector {
 public:
  UnsecureTcpConnector(const std::string& address, unsigned short port);
  ~UnsecureTcpConnector();

  std::shared_ptr<Connection> Connect() override;

  void Connect(
      const std::function<void(const std::shared_ptr<Connection>&)>& onSuccess,
      const std::function<void(const std::exception&)>& onFailure) override;

 private:
  std::string address;
  unsigned short port;

  boost::asio::io_context context;
  boost::asio::ip::tcp::resolver resolver;
};

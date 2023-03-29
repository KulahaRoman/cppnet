#include "unsecuretcpacceptor.h"

UnsecureTcpAcceptor::UnsecureTcpAcceptor(
    const std::shared_ptr<boost::asio::io_context>& context,
    const boost::asio::ip::tcp::endpoint& endpoint)
    : acceptor(*context, endpoint) {}

UnsecureTcpAcceptor::~UnsecureTcpAcceptor() {
  if (acceptor.is_open()) {
    try {
      acceptor.cancel();
      acceptor.close();
    } catch (...) {
      // suppress
    }
  }
}

std::shared_ptr<Connection> UnsecureTcpAcceptor::Accept() {
  std::shared_ptr<Connection> connection;

  try {
    auto socket = acceptor.accept();
    auto stream = std::make_shared<SocketStream>(std::move(socket));

    connection = std::make_shared<UnsecureTcpConnection>(stream);
  } catch (...) {
    throw std::runtime_error("Failed to accept connection.");
  }

  return connection;
}

void UnsecureTcpAcceptor::Accept(
    const std::function<void(const std::shared_ptr<Connection>&)>& onSuccess,
    const std::function<void(const std::exception&)>& onFailure) {
  acceptor.async_accept(
      [onSuccess, onFailure](boost::system::error_code ec,
                             boost::asio::ip::tcp::socket socket) {
        if (ec) {
          if (onFailure) {
            onFailure(std::runtime_error("Failed to accept connection."));
          }
          return;
        }

        auto stream = std::make_shared<SocketStream>(std::move(socket));
        auto connection = std::make_shared<UnsecureTcpConnection>(stream);

        if (onSuccess) {
          onSuccess(connection);
        }
      });
}

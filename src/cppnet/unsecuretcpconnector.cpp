#include "unsecuretcpconnector.h"

UnsecureTcpConnector::UnsecureTcpConnector(const std::string& address,
                                           unsigned short port)
    : address(address), port(port), resolver(context) {}

UnsecureTcpConnector::~UnsecureTcpConnector() { context.stop(); }

std::shared_ptr<Connection> UnsecureTcpConnector::Connect() {
  boost::asio::ip::tcp::socket socket(context);

  try {
    boost::asio::connect(socket,
                         resolver.resolve(address, std::to_string(port)));
  } catch (...) {
    throw std::runtime_error("Client failed to connect the server.");
  }

  auto stream = std::make_shared<SocketStream>(std::move(socket));
  auto connection = std::make_shared<UnsecureTcpConnection>(stream);

  return connection;
}

void UnsecureTcpConnector::Connect(
    const std::function<void(const std::shared_ptr<Connection>&)>& onSuccess,
    const std::function<void(const std::exception&)>& onFailure) {
  resolver.async_resolve(
      address, std::to_string(port),
      [this, onSuccess, onFailure](
          const boost::system::error_code& errc,
          boost::asio::ip::tcp::resolver::results_type results) {
        if (errc) {
          if (onFailure) {
            onFailure(std::runtime_error("Failed to resolve endpoint."));
          }
          return;
        }

        auto socket = std::make_shared<boost::asio::ip::tcp::socket>(context);
        boost::asio::async_connect(
            *socket, results.begin(), results.end(),
            [this, onSuccess, onFailure, socket](const auto& errc,
                                                 auto resultIterator) {
              if (errc) {
                if (onFailure) {
                  onFailure(std::runtime_error("Failed to accept connection."));
                }
                return;
              }

              // idk will it work or no----------------------------->.
              auto stream = std::make_shared<SocketStream>(std::move(*socket));
              auto connection = std::make_shared<UnsecureTcpConnection>(stream);

              if (onSuccess) {
                onSuccess(connection);
              }
            });
      });
}

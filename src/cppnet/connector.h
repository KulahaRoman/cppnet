#pragma once
#include <string>

#include "connection.h"

class Connector {
 public:
  // Synchronous operation. If succeed, returns connection. Throws
  // exception if failed.
  virtual std::shared_ptr<Connection> Connect() = 0;

  // Asynchronous operation. If succeed, passes new connection to 'onSuccess'
  // as argument. Doesn't throw exception, but passes it to 'onFailure' as
  // argument instead.
  virtual void Connect(
      const std::function<void(const std::shared_ptr<Connection>&)>& onSuccess,
      const std::function<void(const std::exception&)>& onFailure) = 0;

  virtual ~Connector() = default;
};

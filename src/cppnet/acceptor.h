#pragma once
#include <functional>
#include <memory>

#include "connection.h"

// Interface, that defines an entity, which accepts connection asynchronously
// and passes it as argument to callback 'onSuccess', or passes an exception to
// callback 'onFailure' in case of failure.
class Acceptor {
 public:
  // Synchronous operation. If succeed, returns connection. Throws
  // exception if failed.
  virtual std::shared_ptr<Connection> Accept() = 0;

  // Asynchronous operation. If succeed, passes new connection to 'onSuccess'
  // as argument. Doesn't throw exception, but passes it to 'onFailure' as
  // argument instead.
  virtual void Accept(
      const std::function<void(const std::shared_ptr<Connection>&)>& onSuccess,
      const std::function<void(const std::exception&)>& onFailure) = 0;

  virtual ~Acceptor() = default;
};

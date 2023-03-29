#pragma once
#include <functional>
#include <memory>

#include "packages/package.h"

class Connection {
 public:
  // Synchronous operation. If succeed, returns received package. Throws
  // exception if failed.
  virtual std::shared_ptr<Package> ReceivePackage() = 0;

  // Asynchronous operation. If succeed, passes received package to 'onSuccess'
  // as argument. Doesn't throw exception, but passes it to 'onFailure' as
  // argument instead.
  virtual void ReceivePackage(
      const std::function<void(const std::shared_ptr<Package>&)>& onSuccess,
      const std::function<void(const std::exception&)>& onFailure) = 0;

  // Synchronous operation. Accepts package to send to as argument. Throws
  // exception if failed.
  virtual void SendPackage(const std::shared_ptr<Package>& package) = 0;

  // Asynchronous operation. If succeed, passes sent package to 'onSuccess' as
  // argument. Doesn't throw exception, but passes it to
  // 'onFailure' as argument instead.
  virtual void SendPackage(
      const std::shared_ptr<Package>& package,
      const std::function<void(const std::shared_ptr<Package>&)>& onSuccess,
      const std::function<void(const std::exception&)>& onFailure) = 0;

  virtual ~Connection() = default;
};

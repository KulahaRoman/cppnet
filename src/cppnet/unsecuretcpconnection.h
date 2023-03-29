#pragma once
#include <cppstreams/stream.h>

#include "connection.h"
#include "packages/packagedecoder.h"
#include "packages/packageencoder.h"

class UnsecureTcpConnection : public Connection {
 public:
  UnsecureTcpConnection(const std::shared_ptr<Stream>& dataStream);

  std::shared_ptr<Package> ReceivePackage() override;

  void ReceivePackage(
      const std::function<void(const std::shared_ptr<Package>&)>& onSuccess,
      const std::function<void(const std::exception&)>& onFailure) override;

  void SendPackage(const std::shared_ptr<Package>& package) override;

  void SendPackage(
      const std::shared_ptr<Package>& package,
      const std::function<void(const std::shared_ptr<Package>&)>& onSuccess,
      const std::function<void(const std::exception&)>& onFailure) override;

 private:
  std::shared_ptr<Stream> dataStream;

  uint64_t receivingPackageSize;
  std::vector<unsigned char> receivingPackageData;

  uint64_t sendingPackageSize;
  std::vector<unsigned char> sendingPackageData;
};

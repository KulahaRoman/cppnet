#include "unsecuretcpconnection.h"

UnsecureTcpConnection::UnsecureTcpConnection(
    const std::shared_ptr<Stream>& dataStream)
    : dataStream(dataStream),
      receivingPackageSize(0ull),
      sendingPackageSize(0ull) {}

std::shared_ptr<Package> UnsecureTcpConnection::ReceivePackage() {
  std::shared_ptr<Package> receivedPackage;

  try {
    dataStream->Read(reinterpret_cast<unsigned char*>(&receivingPackageSize),
                     static_cast<uint64_t>(sizeof(receivingPackageSize)));

    receivingPackageData.resize(static_cast<std::size_t>(receivingPackageSize));

    dataStream->Read(receivingPackageData.data(), receivingPackageSize);

    BinaryArchive packageArchive(
        static_cast<std::size_t>(receivingPackageSize));
    packageArchive.Write(receivingPackageData.data(),
                         static_cast<std::size_t>(receivingPackageSize));

    receivedPackage = PackageDecoder::Decode(packageArchive);
  } catch (...) {
    throw std::runtime_error("Failed to receive package.");
  }

  return receivedPackage;
}

void UnsecureTcpConnection::ReceivePackage(
    const std::function<void(const std::shared_ptr<Package>&)>& onSuccess,
    const std::function<void(const std::exception&)>& onFailure) {
  dataStream->Read(
      reinterpret_cast<unsigned char*>(&receivingPackageSize),
      static_cast<uint64_t>(sizeof(receivingPackageSize)),
      [this, onSuccess, onFailure](auto) {
        receivingPackageData.resize(
            static_cast<std::size_t>(receivingPackageSize));

        dataStream->Read(
            receivingPackageData.data(), receivingPackageSize,
            [this, onSuccess](auto) {
              BinaryArchive packageArchive(
                  static_cast<std::size_t>(receivingPackageSize));
              packageArchive.Write(
                  receivingPackageData.data(),
                  static_cast<std::size_t>(receivingPackageSize));

              auto receivedPackage = PackageDecoder::Decode(packageArchive);

              if (onSuccess) {
                onSuccess(receivedPackage);
              }
            },
            [onFailure](const auto& ex) {
              if (onFailure) {
                onFailure(ex);
              }
            });
      },
      [onFailure](const auto& ex) {
        if (onFailure) {
          onFailure(ex);
        }
      });
}

void UnsecureTcpConnection::SendPackage(
    const std::shared_ptr<Package>& package) {
  try {
    auto packageArchive = PackageEncoder::Encode(package);

    sendingPackageSize = packageArchive.GetSize();
    sendingPackageData = std::vector<unsigned char>(
        packageArchive.GetDataPointer(),
        packageArchive.GetDataPointer() + packageArchive.GetSize());

    dataStream->Write(
        reinterpret_cast<const unsigned char*>(&sendingPackageSize),
        static_cast<uint64_t>(sizeof(sendingPackageSize)));
    dataStream->Write(sendingPackageData.data(), sendingPackageSize);
  } catch (...) {
    throw std::runtime_error("Failed to send package.");
  }
}

void UnsecureTcpConnection::SendPackage(
    const std::shared_ptr<Package>& package,
    const std::function<void(const std::shared_ptr<Package>&)>& onSuccess,
    const std::function<void(const std::exception&)>& onFailure) {
  auto packageArchive = PackageEncoder::Encode(package);

  sendingPackageSize = packageArchive.GetSize();
  sendingPackageData = std::vector<unsigned char>(
      packageArchive.GetDataPointer(),
      packageArchive.GetDataPointer() + packageArchive.GetSize());

  dataStream->Write(
      reinterpret_cast<const unsigned char*>(&sendingPackageSize),
      static_cast<uint64_t>(sizeof(sendingPackageSize)),
      [this, package, onSuccess, onFailure](auto) {
        dataStream->Write(
            sendingPackageData.data(), sendingPackageSize,
            [onSuccess, package](auto) {
              if (onSuccess) {
                onSuccess(package);
              }
            },
            [onFailure](const auto& ex) {
              if (onFailure) {
                onFailure(ex);
              }
            });
      },
      [onFailure](const auto& ex) {
        if (onFailure) {
          onFailure(ex);
        }
      });
}

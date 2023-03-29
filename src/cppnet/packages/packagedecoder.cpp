#include "packagedecoder.h"

std::shared_ptr<Package> PackageDecoder::Decode(BinaryArchive& archive) {
  PackageType type = PackageType::NONE;
  Serializer::Deserialize(reinterpret_cast<int&>(type), archive);

  archive.SetReadPosition(-static_cast<int32_t>(sizeof(PackageType)),
                          BinaryArchive::SeekDirection::RELATIVE);

  std::shared_ptr<Package> package;

  switch (type) {
    case PackageType::AUTH_REQUEST: {
      package = std::make_shared<AuthRequestPackage>();
      break;
    }
    case PackageType::AUTH_RESPONSE: {
      package = std::make_shared<AuthResponsePackage>();
      break;
    }
  }

  if (package) {
    package->Deserialize(archive);
  }

  return package;
}

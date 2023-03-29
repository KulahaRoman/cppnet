#include "authrequestpackage.h"

AuthRequestPackage::AuthRequestPackage() : Package(PackageType::AUTH_REQUEST) {}

void AuthRequestPackage::Serialize(BinaryArchive& archive) const {
  Package::Serialize(archive);
}

void AuthRequestPackage::Deserialize(BinaryArchive& archive) {
  Package::Deserialize(archive);
}

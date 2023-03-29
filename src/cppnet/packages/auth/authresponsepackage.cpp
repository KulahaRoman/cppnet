#include "authresponsepackage.h"

AuthResponsePackage::AuthResponsePackage()
    : Package(PackageType::AUTH_RESPONSE) {}

void AuthResponsePackage::Serialize(BinaryArchive& archive) const {
  Package::Serialize(archive);
}

void AuthResponsePackage::Deserialize(BinaryArchive& archive) {
  Package::Deserialize(archive);
}

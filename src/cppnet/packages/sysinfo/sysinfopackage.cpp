#include "sysinfopackage.h"

SysInfoPackage::SysInfoPackage() : Package(PackageType::SYS_INFO) {}

SysInfoPackage::SysInfoPackage(const SystemInformation& info)
    : Package(PackageType::SYS_INFO), info(info) {}

SystemInformation SysInfoPackage::GetSystemInformation() const { return info; }

void SysInfoPackage::SetSystemInformation(const SystemInformation& info) {
  this->info = info;
}

void SysInfoPackage::Serialize(BinaryArchive& archive) const {
  Package::Serialize(archive);
  Serializer::Serialize(info, archive);
}

void SysInfoPackage::Deserialize(BinaryArchive& archive) {
  Package::Deserialize(archive);
  Serializer::Deserialize(info, archive);
}

#pragma once
#include "../package.h"
#include "systeminformation.h"

class SysInfoPackage : public Package {
 public:
  SysInfoPackage();
  SysInfoPackage(const SystemInformation& info);

  SystemInformation GetSystemInformation() const;
  void SetSystemInformation(const SystemInformation& info);

  void Serialize(BinaryArchive& archive) const override;
  void Deserialize(BinaryArchive& archive) override;

 private:
  SystemInformation info;
};

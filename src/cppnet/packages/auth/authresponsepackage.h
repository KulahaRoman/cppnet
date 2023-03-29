#pragma once
#include "../package.h"

class AuthResponsePackage : public Package {
 public:
  AuthResponsePackage();

  void Serialize(BinaryArchive& archive) const override;
  void Deserialize(BinaryArchive& archive) override;
};

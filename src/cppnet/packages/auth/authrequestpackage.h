#pragma once
#include "../package.h"

class AuthRequestPackage : public Package {
 public:
  AuthRequestPackage();

  void Serialize(BinaryArchive& archive) const override;
  void Deserialize(BinaryArchive& archive) override;
};

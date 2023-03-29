#pragma once
#include "auth/authrequestpackage.h"
#include "auth/authresponsepackage.h"
#include "package.h"

class PackageDecoder {
 public:
  static std::shared_ptr<Package> Decode(BinaryArchive& archive);
};

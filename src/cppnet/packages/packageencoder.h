#pragma once
#include "package.h"

class PackageEncoder {
 public:
  static BinaryArchive Encode(const std::shared_ptr<Package>& package);
};

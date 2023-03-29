#include "packageencoder.h"

BinaryArchive PackageEncoder::Encode(const std::shared_ptr<Package>& package) {
  BinaryArchive archive;
  package->Serialize(archive);
  return archive;
}

#pragma once
#include <cpputils/serialization/serializer.h>

#include "../machine.h"
#include "packagetype.h"

class Package : public Serializable {
 public:
  virtual ~Package() = default;

  PackageType GetType() const;
  void SetType(PackageType type);

  Machine GetSender() const;
  void SetSender(const Machine& machine);

  Machine GetReceiver() const;
  void SetReceiver(const Machine& machine);

  virtual void Serialize(BinaryArchive& archive) const override;
  virtual void Deserialize(BinaryArchive& archive) override;

 protected:
  Package(PackageType type);

 private:
  PackageType type;
  Machine sender;
  Machine receiver;
};

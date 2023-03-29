#pragma once
#include <cpputils/serialization/serializer.h>

#include <string>

enum class MachineType { NONE, OPERATOR, SERVER, TARGET };

class Machine : public Serializable {
 public:
  Machine();
  Machine(MachineType type, const std::string& name);

  void SetType(MachineType type);
  MachineType GetType() const;

  void SetName(const std::string& name);
  std::string GetName() const;

  void Serialize(BinaryArchive& archive) const override;
  void Deserialize(BinaryArchive& archive) override;

  operator bool() const;
  bool operator<(const Machine& other) const;

 private:
  MachineType type;
  std::string name;
};

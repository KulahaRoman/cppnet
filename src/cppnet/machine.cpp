#include "machine.h"

Machine::Machine() : type(MachineType::NONE) {}

Machine::Machine(MachineType type, const std::string& name)
    : type(type), name(name) {}

void Machine::SetType(MachineType type) { this->type = type; }

MachineType Machine::GetType() const { return type; }

void Machine::SetName(const std::string& name) { this->name = name; }

std::string Machine::GetName() const { return name; }

void Machine::Serialize(BinaryArchive& archive) const {
  Serializer::Serialize(static_cast<int>(type), archive);
  Serializer::Serialize(name, archive);
}

void Machine::Deserialize(BinaryArchive& archive) {
  Serializer::Deserialize(reinterpret_cast<int&>(type), archive);
  Serializer::Deserialize(name, archive);
}

Machine::operator bool() const { return this->type != MachineType::NONE; }

bool Machine::operator<(const Machine& other) const {
  return this->name < other.name;
}

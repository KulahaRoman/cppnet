#include "package.h"

Package::Package(PackageType type) : type(type) {}

PackageType Package::GetType() const { return type; }

void Package::SetType(PackageType type) { this->type = type; }

Machine Package::GetSender() const { return sender; }

void Package::SetSender(const Machine& machine) { sender = machine; }

Machine Package::GetReceiver() const { return receiver; }

void Package::SetReceiver(const Machine& machine) { receiver = machine; }

void Package::Serialize(BinaryArchive& archive) const {
  Serializer::Serialize(static_cast<int>(type), archive);
  Serializer::Serialize(sender, archive);
  Serializer::Serialize(receiver, archive);
}

void Package::Deserialize(BinaryArchive& archive) {
  Serializer::Deserialize(reinterpret_cast<int&>(type), archive);
  Serializer::Deserialize(sender, archive);
  Serializer::Deserialize(receiver, archive);
}

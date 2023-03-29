#include "machinehelper.h"

Machine MachineHelper::GetCurrentMachine() {
  MachineType type = MachineType::NONE;

#ifdef SERVER_MACHINE
  type = MachineType::SERVER;
#elif TARGET_MACHINE
  type = MachineType::TARGET;
#elif OPERATOR_MACHINE
  type = MachineType::OPERATOR;
#else
  type = MachineType::NONE;
#endif

  constexpr int BUFFER_SIZE = 512;
  std::vector<char> buffer(BUFFER_SIZE);
  unsigned long bufferSize = BUFFER_SIZE;

  std::string hostName;

#ifdef __linux__
  if (!gethostname(buffer.data(), BUFFER_SIZE)) {
    hostName += buffer.data();
  } else {
    hostName += "PC";
  }
#elif _WIN32
  if (GetComputerNameA(buffer.data(), &bufferSize)) {
    hostName += buffer.data();
  } else {
    hostName += "PC";
  }
#endif

  hostName += ":";

#ifdef __linux__
  if (!getlogin_r(buffer.data(), BUFFER_SIZE)) {
    hostName += buffer.data();
  } else {
    hostName += "user";
  }
#elif _WIN32
  if (GetUserNameA(buffer.data(), &bufferSize)) {
    hostName += buffer.data();
  } else {
    hostName += "user";
  }
#endif

  Machine machine;
  machine.SetType(type);
  machine.SetName(hostName);

  return machine;
}

std::string MachineHelper::MachineTypeToString(MachineType type) {
  switch (type) {
    case MachineType::TARGET:
      return "TARGET";
    case MachineType::SERVER:
      return "SERVER";
    case MachineType::OPERATOR:
      return "OPERATOR";
    default:
      return "NONE";
  }
}

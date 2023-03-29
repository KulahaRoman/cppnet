#pragma once
#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include "machine.h"

class MachineHelper {
 public:
  static Machine GetCurrentMachine();
  static std::string MachineTypeToString(MachineType type);
};

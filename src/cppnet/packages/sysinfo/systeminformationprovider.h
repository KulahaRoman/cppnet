#pragma once
#define WIN32_LEAN_AND_MEAN
// #include <VersionHelpers.h>
#include <Windows.h>

#include <chrono>

#include "systeminformation.h"

class SystemInformationProvider {
 public:
  static SystemInformation CollectSystemInformation();
};

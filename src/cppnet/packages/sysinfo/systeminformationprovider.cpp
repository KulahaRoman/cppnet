#include "systeminformationprovider.h"

SystemInformation SystemInformationProvider::CollectSystemInformation() {
  SystemInformation sysInfo;

  constexpr int BUFFER_SIZE = 32767;
  std::vector<char> buffer(BUFFER_SIZE);
  unsigned long bufferSize = BUFFER_SIZE;

  // User name
  if (GetUserNameA(buffer.data(), &bufferSize)) {
    sysInfo.SetUserName(buffer.data());
  }

  // Host name
  if (GetComputerNameA(buffer.data(), &bufferSize)) {
    sysInfo.SetHostName(buffer.data());
  }

  // CPU arch

  // Local time
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);

  sysInfo.SetLocalTime(std::ctime(&time));

  // System directory
  if (GetSystemDirectoryA(buffer.data(), bufferSize)) {
    sysInfo.SetSystemDirectory(buffer.data());
  }

  // Windows directory
  if (GetWindowsDirectoryA(buffer.data(), bufferSize)) {
    sysInfo.SetWindowsDirectory(buffer.data());
  }

  return sysInfo;
}

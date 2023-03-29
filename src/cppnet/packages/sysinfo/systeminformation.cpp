#include "systeminformation.h"

SystemInformation::SystemInformation() {}

std::string SystemInformation::GetHostName() const { return hostName; }

void SystemInformation::SetHostName(const std::string& name) {
  this->hostName = name;
}

std::string SystemInformation::GetUserName() const { return userName; }

void SystemInformation::SetUserName(const std::string& name) {
  this->userName = name;
}

std::string SystemInformation::GetCPUArchitecture() const {
  return cpuArchitecture;
}

void SystemInformation::SetCPUArchitecture(const std::string& arch) {
  this->cpuArchitecture = arch;
}

std::string SystemInformation::GetLocalTime() const { return localTime; }

void SystemInformation::SetLocalTime(const std::string& time) {
  this->localTime = time;
}

std::string SystemInformation::GetSystemDirectory() const {
  return systemDirectory;
}

void SystemInformation::SetSystemDirectory(const std::string& directory) {
  this->systemDirectory = directory;
}

std::string SystemInformation::GetWindowsDirectory() const {
  return windowsDirectory;
}

void SystemInformation::SetWindowsDirectory(const std::string& directory) {
  this->windowsDirectory = directory;
}

std::string SystemInformation::GetSystemVersion() const {
  return systemVersion;
}

void SystemInformation::SetSystemVersion(const std::string& version) {
  this->systemVersion = version;
}

std::vector<std::string> SystemInformation::GetLogicalDrives() const {
  return logicalDrives;
}

void SystemInformation::SetLogicalDrives(
    const std::vector<std::string>& drives) {
  this->logicalDrives = drives;
}

std::vector<std::pair<std::string, std::string>>
SystemInformation::GetEnvironmentVariables() const {
  return envVars;
}

void SystemInformation::SetEnvironmentVariables(
    const std::vector<std::pair<std::string, std::string>>& vars) {
  this->envVars = vars;
}

void SystemInformation::Serialize(BinaryArchive& archive) const {
  Serializer::Serialize(hostName, archive);
  Serializer::Serialize(userName, archive);
  Serializer::Serialize(cpuArchitecture, archive);
  Serializer::Serialize(localTime, archive);
  Serializer::Serialize(systemDirectory, archive);
  Serializer::Serialize(windowsDirectory, archive);
  Serializer::Serialize(systemVersion, archive);
  Serializer::Serialize(logicalDrives, archive);
  Serializer::Serialize(envVars, archive);
}

void SystemInformation::Deserialize(BinaryArchive& archive) {
  Serializer::Deserialize(hostName, archive);
  Serializer::Deserialize(userName, archive);
  Serializer::Deserialize(cpuArchitecture, archive);
  Serializer::Deserialize(localTime, archive);
  Serializer::Deserialize(systemDirectory, archive);
  Serializer::Deserialize(windowsDirectory, archive);
  Serializer::Deserialize(systemVersion, archive);
  Serializer::Deserialize(logicalDrives, archive);
  Serializer::Deserialize(envVars, archive);
}

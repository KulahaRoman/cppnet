#pragma once
#include <cpputils/serialization/serializer.h>

class SystemInformation : public Serializable {
 public:
  SystemInformation();

  std::string GetHostName() const;
  void SetHostName(const std::string& name);

  std::string GetUserName() const;
  void SetUserName(const std::string& name);

  std::string GetCPUArchitecture() const;
  void SetCPUArchitecture(const std::string& arch);

  std::string GetLocalTime() const;
  void SetLocalTime(const std::string& time);

  std::string GetSystemDirectory() const;
  void SetSystemDirectory(const std::string& directory);

  std::string GetWindowsDirectory() const;
  void SetWindowsDirectory(const std::string& directory);

  std::string GetSystemVersion() const;
  void SetSystemVersion(const std::string& version);

  std::vector<std::string> GetLogicalDrives() const;
  void SetLogicalDrives(const std::vector<std::string>& drives);

  std::vector<std::pair<std::string, std::string>> GetEnvironmentVariables()
      const;
  void SetEnvironmentVariables(
      const std::vector<std::pair<std::string, std::string>>& vars);

  void Serialize(BinaryArchive& archive) const override;
  void Deserialize(BinaryArchive& archive) override;

 private:
  std::string hostName;
  std::string userName;
  std::string cpuArchitecture;
  std::string localTime;
  std::string systemDirectory;
  std::string windowsDirectory;
  std::string systemVersion;
  std::vector<std::string> logicalDrives;
  std::vector<std::pair<std::string, std::string>> envVars;
};

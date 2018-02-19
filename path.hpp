#pragma once

#include <string>
#include <cstdlib>

namespace mfl {
  namespace path {

    inline std::string getHomePath() {
#ifdef WIN32
      auto homePath = std::getenv("USERPROFILE");
      if (homePath) return homePath;

      auto homeDrive = std::getenv("HOMEDRIVE");
      if (homeDrive) {
        homePath = std::getenv("HOMEPATH");
        return {homeDrive + homePath};
      }
#else
      auto homePath = std::getenv("HOME");
      if (homePath) return homePath;
#endif
      return "";
    }

    inline std::string getDataPath() {
#ifdef WIN32
      auto homePath = getHomePath();
      if (!homePath.empty()) return {homePath + "/AppData/Roaming"};
#else
      auto configPath = std::getenv("$XDG_DATA_HOME");
      if (configPath) return configPath;

      auto homePath = getHomePath();
      if (!homePath.empty()) return {homePath + "/.local/share"};
#endif
      return "";
    }

    inline std::string getConfigPath() {
      auto configPath = std::getenv("$XDG_CONFIG_HOME");
      if (configPath) return configPath;

      auto homePath = getHomePath();
      if (!homePath.empty()) {
#ifdef WIN32
        return {homePath + "/AppData/Roaming"};
#else
        return {homePath + "/.config"};
#endif
      }

      return "";
    }

    inline std::string getTempPath() {
#ifdef WIN32
      auto homePath = getHomePath();
      if (!homePath.empty()) return {homePath + "/AppData/Local/Temp"};
#else
      auto tempPath = std::getenv("TMPDIR");
      if (tempPath) return tempPath;

      return "/tmp";
#endif
      return "";
    }
  }
}

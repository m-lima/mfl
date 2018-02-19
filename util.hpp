#pragma once

#include <string>
#include <algorithm>
#include <functional>
#include <cstdlib>

#include <fmt/format.h>

namespace mfl {
  namespace util {

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
      auto configPath = std::getenv("$XDG_DATA_HOME");
      if (configPath) return configPath;

      auto homePath = getHomePath();
      if (!homePath.empty()) {
#ifdef WIN32
        return {homePath + "/AppData/Roaming"};
#else
        return {homePath + "/.local/share"};
#endif
      }

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

    inline bool isBigEndian() {
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || \
    defined(__BIG_ENDIAN__) || \
    defined(__ARMEB__) || \
    defined(__THUMBEB__) || \
    defined(__AARCH64EB__) || \
    defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
      return true;
#elif defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || \
    defined(__LITTLE_ENDIAN__) || \
    defined(__ARMEL__) || \
    defined(__THUMBEL__) || \
    defined(__AARCH64EL__) || \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
      return false;
#else
#error "Could not detect endianess"
#endif
    }
  }
}

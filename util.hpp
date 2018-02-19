#pragma once

#include <string>
#include <algorithm>
#include <functional>

#include <fmt/format.h>

namespace mfl {
  namespace util {
    inline std::string getHomeFolder() {
#ifdef WIN32
      auto homePath = getenv("USERPROFILE");
      if (homePath) return homePath;

      auto homeDrive = getenv("HOMEDRIVE");
      if (homeDrive) {
        homePath = getenv("HOMEPATH");
        return std::string(homeDrive + homePath);
      }
#else
      auto homePath = getenv("HOME");
      if (homePath) return homePath;
#endif
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

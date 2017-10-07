#pragma once

#include <string>
#include <algorithm>
#include <functional>

#include <fmt/format.h>

namespace util {

  /////////////////////////////////////
  // String handling
  inline void trimInPlace(std::string & str) {
    // Left trim
    str.erase(
        str.begin(),
        std::find_if(str.begin(),
                     str.end(),
                     std::not1(std::ptr_fun<int, int>(std::isspace)))
    );

    // Right trim
    str.erase(
        std::find_if(str.rbegin(),
                     str.rend(),
                     std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
        str.end()
    );
  }

  inline std::string trim(const std::string & str) {
    std::string returnString(str);
    trimInPlace(returnString);
    return returnString;
  }

  inline uint8_t toUint8(const char character) {
    if (character >= 48 && character < 58) {
      return character - 48;
    }

    if (character >= 65 && character < 71) {
      return character - 55;
    }

    if (character >= 97 && character < 103) {
      return character - 87;
    }

    return -1;
  }

  inline const std::string simplifyValue(double value) {
    if (value < 1000) {
      return fmt::format("{:d}", value);
    }

    value /= 1000.0;
    if (value < 1000) {
      return fmt::format("{:03.2f} thousand", value);
    }

    value /= 1000.0;
    if (value < 1000) {
      return fmt::format("{:03.2f} million", value);
    }

    value /= 1000.0;
    if (value < 1000) {
      return fmt::format("{:03.2f} billion", value);
    }

    value /= 1000.0;
    if (value < 1000) {
      return fmt::format("{:03.2f} trillion", value);
    }

    return "<invalid>";
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

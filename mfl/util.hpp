#pragma once

#include <string>
#include <algorithm>

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

  template <bool x64>
  inline bool isBigEndian() {
    if (x64) {
      union {
        uint64_t i;
        char c[8];
      } testValue = { 0x0102030405060708 };
    } else {
      union {
        uint32_t i;
        char c[4];
      } testValue = { 0x01020304 };
    }

    return testValue.c[0] == 1;
  }
}

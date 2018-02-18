#pragma once

#include <string>
#include <algorithm>
#include <functional>

#include <fmt/format.h>

namespace mfl {
  namespace string {

    /////////////////////////////////////
    // String handling
    inline std::string toLower(const std::string & str) {
      std::string out;
      std::transform(str.cbegin(), str.cend(), std::back_inserter(out), ::tolower);
      return out;
    }

    inline std::string toUpper(const std::string & str) {
      std::string out;
      std::transform(str.cbegin(), str.cend(), std::back_inserter(out), ::toupper);
      return out;
    }

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
        return fmt::format("{:03.2f}", value);
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

    inline std::string durationToString(long millis) {
      long seconds = millis / 1000;
      int minutes = seconds / 60;
      int hours = minutes / 60;
      minutes %= 60;
      seconds %= 60;
      millis %= 1000;

      std::string format;
      if (hours > 0) {
        format.append(fmt::format("{:d}h ", hours));
      }
      if (minutes > 0 || hours > 0) {
        format.append(fmt::format("{:d}m ", minutes));
      }
      format.append(fmt::format("{:d}.{:03d}s", seconds, millis));

      return format;
    }
  }
}

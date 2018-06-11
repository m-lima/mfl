#pragma once

#include <string>
#include <vector>
#include <sstream>
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

    inline std::vector<std::string> split(const std::string & str, char delimiter) {
      std::vector<std::string> out{};
      std::stringstream stringStream{str};
      std::string item;

      while (std::getline(stringStream, item, delimiter)) {
        out.push_back(item);
      }

      return out;
    }

    inline bool startsWith(const std::string & str, const std::string & prefix) {
      if (str.size() < prefix.size()) {
        return false;
      }

      return std::equal(prefix.cbegin(), prefix.cend(), str.cbegin());
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

    /**
     * Taken and adapted from from my good friend jodleif at:
     * https://github.com/jodleif/strhashliteral
     */
    namespace hash32 {
      constexpr static std::uint32_t prime{16'777'619u};
      constexpr static std::uint32_t offset{2'166'136'261u};

      /**
       * Hash until null termination
       *
       * @param toHash string to hash
       * @return the hashed version
       */
      inline constexpr std::uint32_t hash(const char * toHash) {
        std::uint32_t hash{offset};
        const char * hashed{toHash};

        for (;; ++hashed) {
          if (*hashed == 0)
            break;
          hash *= prime;
          hash ^= *hashed;
        }

        return hash;
      }

      /**
       * Hash until length
       *
       * @param toHash string to hash
       * @param length length to hash
       * @return the hashed version
       */
      inline constexpr std::uint32_t hash(const char * toHash, std::size_t length) {
        std::uint32_t hash{offset};
        const char * hashed{toHash};

        for (std::size_t i{0}; i < length; ++i, ++hashed) {
          hash *= prime;
          hash ^= *hashed;
        }

        return hash;
      }

      inline std::uint32_t hash(const std::string & toHash) {
        return hash(toHash.c_str(), toHash.length());
      }

      inline constexpr std::uint32_t operator "" _h(const char * string, std::size_t len) {
        return hash(string, len);
      }
    }

    namespace hash64 {
      constexpr static std::uint64_t prime{1'099'511'628'211ull};
      constexpr static std::uint64_t offset{14'695'981'039'346'656'037ull};

      /**
       * Hash until null termination
       *
       * @param toHash string to hash
       * @return the hashed version
       */
      inline constexpr std::uint64_t hash(const char * toHash) {
        std::uint64_t hash{offset};
        const char * hashed{toHash};

        for (;; ++hashed) {
          if (*hashed == 0)
            break;
          hash = hash * prime;
          hash = hash ^ *hashed;
        }

        return hash;
      }

      /**
       * Hash until length
       *
       * @param toHash string to hash
       * @param length length to hash
       * @return the hashed version
       */
      inline constexpr std::uint64_t hash(const char * toHash, std::size_t length) {
        std::uint64_t hash{offset};
        const char * hashed{toHash};

        for (std::size_t i{0}; i < length; ++i, ++hashed) {
          hash = hash * prime;
          hash = hash ^ *hashed;
        }

        return hash;
      }

      inline std::uint64_t hash(const std::string & toHash) {
        return hash(toHash.c_str(), toHash.length());
      }

      inline constexpr std::uint64_t operator "" _h(const char * string, std::size_t len) {
        return hash(string, len);
      }
    }
  }
}


#pragma once

namespace mfl {
  namespace util {
    constexpr bool isBigEndian() {
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

    template <typename T, typename E>
    constexpr T safeCast(E value) {
        return static_cast<T>(value & ~(1 << ((sizeof(T) << 3) - 1)));
    }
  }
}

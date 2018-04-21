#pragma once

namespace mfl {
  namespace util {
    constexpr bool isBigEndian() const {
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN \
   || defined(__BIG_ENDIAN__) \
   || defined(__i386__) || defined(__alpha__) \
   || defined(__ia64) || defined(__ia64__) \
   || defined(_M_IX86) || defined(_M_IA64) \
   || defined(_M_ALPHA) || defined(__amd64) \
   || defined(__amd64__) || defined(_M_AMD64) \
   || defined(__x86_64) || defined(__x86_64__) \
   || defined(_M_X64) || defined(__bfin__) \
   || defined(__ARMEB__) \
   || defined(__THUMBEB__) \
   || defined(__AARCH64EB__) \
   || defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
      return true;
#elif defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN \
   || defined(__LITTLE_ENDIAN__) \
   || defined(__sparc) || defined(__sparc__) \
   || defined(_POWER) || defined(__powerpc__) \
   || defined(__ppc__) || defined(__hpux) || defined(__hppa) \
   || defined(_MIPSEB) || defined(_POWER) \
   || defined(__s390__) \
   || defined(__ARMEL__) \
   || defined(__THUMBEL__) \
   || defined(__AARCH64EL__) \
   || defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
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

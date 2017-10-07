#pragma once

#include <string>

#include <fmt/ostream.h>

namespace util {

  /////////////////////////////////////
  // Print handling
  template <typename ... Args>
  inline void println(const char * const format, const Args & ... args) {
    std::string lineBreakFormat(format);
    lineBreakFormat.append("\n");
    fmt::print(lineBreakFormat, args...);
  }

  template <typename ... Args>
  inline void println(std::FILE * file,
                      const char * const format,
                      const Args & ... args) {
    std::string lineBreakFormat(format);
    lineBreakFormat.append("\n");
    fmt::print(file, lineBreakFormat, args...);
  }

  inline void println(const std::string & string) {
    std::string lineBreakFormat(string);
    lineBreakFormat.append("\n");
    fmt::print(lineBreakFormat);
  }

  inline void println() {
    fmt::print("\n");
  }

  inline void println(std::FILE * file) {
    fmt::print(file, "\n");
  }

}

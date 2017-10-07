#pragma once

#include <chrono>

#include <fmt/format.h>

#include "ostream.hpp"

namespace util {
  class Timer {
  private:
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;

  public:
    Timer() = default;

    inline void start() {
      begin = std::chrono::high_resolution_clock::now();
    }

    inline void stop() {
      end = std::chrono::high_resolution_clock::now();
    }

    inline auto getDuration() {
      return
          std::
          chrono::
          duration_cast<std::chrono::milliseconds>(end - begin).count();
    }

    inline void printDuration() {
      auto millis = getDuration();

      long seconds = millis / 1000;
      int minutes = seconds / 60;
      int hours = minutes / 60;
      minutes %= 60;
      seconds %= 60;
      millis %= 1000;

      fmt::print("Elapsed time: ");
      if (hours > 0) {
        fmt::print("{:d}h ", hours);
      }
      if (minutes > 0 || hours > 0) {
        fmt::print("{:d}m ", minutes);
      }
      util::println("{:d}.{:03d}s", seconds, millis);
    }
  };
}

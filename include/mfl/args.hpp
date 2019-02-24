#pragma once

#include <string>
#include <algorithm>

namespace mfl {
  namespace args {

    /////////////////////////////////////
    // Argument handling
    inline char * extractOption(int argc, char * argv[], const std::string & option) {
      auto end = argc + argv;
      char ** itr = std::find(argv, end, option);
      if (itr != end && ++itr != end) {
        return *itr;
      }
      return 0;
    }

    inline bool findOption(int argc, char * argv[], const std::string & option) {
      return std::find(argv, argv + argc, option) != argv + argc;
    }

  }
}

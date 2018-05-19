#pragma once

#include <string>
#include <algorithm>

namespace mfl {
  namespace args {

    /////////////////////////////////////
    // Argument handling
    inline char * extractOption(char * begin[],
                                char * end[],
                                const std::string & option) {
      char ** itr = std::find(begin, end, option);
      if (itr != end && ++itr != end) {
        return *itr;
      }
      return 0;
    }

    inline bool findOption(char * begin[],
                           char * end[],
                           const std::string & option) {
      return std::find(begin, end, option) != end;
    }

  }
}

#pragma once

#include <string>
#include <fstream>

#include <fmt/format.h>

#include "exception.hpp"

namespace mfl {
  namespace file {

    /////////////////////////////////////
    // File handling
    inline bool testFileExists(const char * fileName) {
      if (!fileName) {
        return false;
      }

      std::ifstream testOutput(fileName);
      if (testOutput.is_open()) {
        testOutput.close();
        return true;
      }

      return false;
    }

    template<int MaxTries = 20>
    inline void guaranteeNewFile(std::string & path,
                                 const std::string & extension) {
      // Check if the file exists
      // Keep appending ".new" before the extension until
      // the filename is unique
      int counter = 0;
      do {

        // Try to read it
        std::ifstream testFile(path);

        // If it's not readable, it doesn't exits; Quit loop
        if (!testFile.is_open()) {
          break;
        }

        testFile.close();

        // Find the extension
        auto index = path.rfind("." + extension);

        // If it has no extension, first try adding an extension to it
        if (index == std::string::npos) {
          path = fmt::format("{}.{}", path, extension);
        }
          // If it does, append ".new" before the extension
        else {
          path = fmt::format("{}.new.{}", path.substr(0, index), extension);
        }

        counter++;
      } while (counter < MaxTries);

      if (counter == MaxTries) {
        throw mfl::Exception::build("Could not write to file. Too many copies exist");
      }
    }
  }
}

from conans import ConanFile, CMake, tools
import os

class MflTestConan(ConanFile):
    requires = "mfl/1.0@mfl/stable"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if not tools.cross_building(self.settings):
            os.chdir("bin")
            self.run(".%stest" % os.sep)

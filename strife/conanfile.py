from conans import ConanFile, CMake

class StrifeConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "eigen/3.3.4@conan/stable", "jsonformoderncpp/3.2.0@vthiery/stable", "sdl2/2.0.8@bincrafters/stable", "sdl2_image/2.0.3@bincrafters/stable", "boost_uuid/1.66.0@bincrafters/stable", "boost_filesystem/1.66.0@bincrafters/stable"#, "emsdk_installer/1.38.0@bincrafters/testing"
   generators = "cmake"
   #settings = {"compiler": "clang"}

   # def build(self):
   #    cmake = CMake(self)
   #    cmake.configure()
   #    cmake.build()

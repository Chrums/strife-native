from conans import ConanFile, CMake

class StrifeConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "eigen/3.3.4@conan/stable", "jsonformoderncpp/3.2.0@vthiery/stable"
   generators = "cmake", "gcc"

   def build(self):
      cmake = CMake(self)
      cmake.configure()
      cmake.build()
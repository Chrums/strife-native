from conans import ConanFile, CMake

class StrifeConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "eigen/3.3.4@conan/stable", "jsonformoderncpp/3.2.0@vthiery/stable" # comma-separated list of requirements
   generators = "cmake", "gcc"
   #default_options = "Poco:shared=True", "OpenSSL:shared=True"

#   def imports(self):
#       self.copy("*.dll", dst="bin", src="bin") # From bin to bin
#       self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin

   def build(self):
      cmake = CMake(self)
      cmake.configure()
      cmake.build()
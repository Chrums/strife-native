from conans import ConanFile, CMake

class StrifeConan(ConanFile):
   
   settings = "os", "compiler", "build_type", "arch"
   
   requires = "eigen/3.3.4@conan/stable", \
        "jsonformoderncpp/3.2.0@vthiery/stable", \
        "boost_uuid/1.66.0@bincrafters/stable", \
        "boost_filesystem/1.66.0@bincrafters/stable"
        
   generators = "cmake"
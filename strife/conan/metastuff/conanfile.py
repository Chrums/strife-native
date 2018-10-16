from conans import ConanFile, CMake, tools
import os


class MetaStuff(ConanFile):
    name = "metastuff"
    version = "cmake"
    settings = "os", "compiler", "arch", "build_type"
    description = "JSON for Modern C++ parser and generator from https://github.com/nlohmann/json"
    license = "MIT"
    url = "https://github.com/thormme/conan-metastuff"
    repo_url = "https://github.com/eliasdaler/MetaStuff"
    author = "Michael Schroder (michael@schroder.space)"

    def source(self):
        tools.get("%s/archive/%s.zip" % (self.repo_url, self.version))

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="MetaStuff-%s" % self.version)
        cmake.install()

    def package(self):
        self.copy("LICENSE", src="MetaStuff-%s" % self.version)

    def package_id(self):
        self.info.header_only()

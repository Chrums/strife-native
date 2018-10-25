cmake_minimum_required(VERSION 3.0)
project(strife)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.12/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

find_program(CONAN_CMD conan)
if(NOT CONAN_CMD AND CONAN_REQUIRED)
    message(FATAL_ERROR "Conan executable not found!")
endif()

conan_cmake_run(CONANFILE conanfile.py
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Threads REQUIRED)

add_subdirectory(core)

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

include_directories(AFTER SYSTEM
    ${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES}
)

target_link_libraries(main LINK_PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    core
)

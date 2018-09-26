cmake_minimum_required(VERSION 3.0)
project(strife)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_FLAGS "--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/project")

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_subdirectory(core)

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

target_link_libraries(main LINK_PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    core
)
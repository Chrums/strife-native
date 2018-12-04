cmake_minimum_required(VERSION 3.0)
project(strife)

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

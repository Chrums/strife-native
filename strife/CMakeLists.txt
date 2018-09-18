cmake_minimum_required(VERSION 3.0)
project(strife)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

#set(CMAKE_CXX_FLAGS "--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/project")

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_subdirectory(core)
add_subdirectory(project)

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

target_link_libraries(main LINK_PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    core
    project
)

#set_target_properties(main PROPERTIES
#    SUFFIX ".js"
#    LINK_FLAGS "-s WASM=0 -s USE_PTHREADS=1 -s DEMANGLE_SUPPORT=1 -s DISABLE_EXCEPTION_CATCHING=0"
#)
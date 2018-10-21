cmake_minimum_required(VERSION 3.0)
project(strife)

add_definitions(-DBUILDING_NODE_EXTENSION)
add_definitions(-DUSING_V8_SHARED)
add_definitions(-DUSING_UV_SHARED)
add_definitions(-DV8_DEPRECATION_WARNINGS)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
execute_process(COMMAND ${CONAN_CMD} export ${CMAKE_CURRENT_SOURCE_DIR}/conan/sdl2_ttf currentproject/stable)
execute_process(COMMAND ${CONAN_CMD} export ${CMAKE_CURRENT_SOURCE_DIR}/conan/metastuff currentproject/stable)
execute_process(COMMAND ${CONAN_CMD} export ${CMAKE_CURRENT_SOURCE_DIR}/conan/imgui currentproject/stable)

conan_cmake_run(CONANFILE conanfile.py
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_FLAGS "--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/project")

find_package(Threads REQUIRED)

add_subdirectory(core)
add_subdirectory(project)
add_subdirectory(nbind)

add_library(main SHARED main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

set_target_properties(main PROPERTIES PREFIX "" SUFFIX ".node")

message("JS LIB ${CMAKE_JS_LIB}")

include_directories(AFTER SYSTEM
    ${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES}
    #/home/michael/projects/v8/include
    /home/michael/.cmake-js/node-x64/v10.11.0/include/node
    ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/nan
    ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/nbind/include
)

#link_directories(/home/michael/projects/v8/out.gn/x64.release.sample/obj/)

target_link_libraries(main LINK_PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    ${CONAN_LIBS_SDL2}
    core
    project
    nbind
    ${CMAKE_JS_LIB}
    #/home/michael/projects/v8/out.gn/x64.release.sample/obj/libv8_monolith.a
)




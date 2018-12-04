cmake_minimum_required(VERSION 3.5.1)
project(strife)

if(CMAKE_CXX_COMPILER MATCHES "em\\+\\+$")
    set(EMSCRIPTEN TRUE)
else()
    set(EMSCRIPTEN FALSE)
endif()

if(NOT EMSCRIPTEN)
    find_package(Boost 1.66.0 REQUIRED)
endif()

add_subdirectory(core)

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

target_include_directories(main PUBLIC
    ${BOOST_ROOT}
)

target_link_libraries(main LINK_PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    core
)

if(EMSCRIPTEN)
    set_target_properties(main PROPERTIES
        SUFFIX ".js"
        LINK_FLAGS "-s WASM=0 -s DEMANGLE_SUPPORT=1 -s DISABLE_EXCEPTION_CATCHING=0"
    )
endif()
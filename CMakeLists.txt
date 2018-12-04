cmake_minimum_required(VERSION 3.5.1)
project(strife)

#find_package(Threads REQUIRED)

add_subdirectory(core)

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

target_include_directories(main PUBLIC
    ${BOOST_ROOT}
)

target_link_libraries(main LINK_PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    ${BOOST_ROOT}/stage/lib
    core
)

if(${CMAKE_CXX_COMPILER} STREQUAL "em++")
    set_target_properties(main PROPERTIES
        SUFFIX ".js"
        LINK_FLAGS "-s WASM=0 -s USE_PTHREADS=1 -s DEMANGLE_SUPPORT=1 -s DISABLE_EXCEPTION_CATCHING=0"
    )
endif()
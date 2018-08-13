cmake_minimum_required(VERSION 3.0)
project(strife)

message(WARNING ${BOOST_ROOT})

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_subdirectory(core)

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
target_link_libraries(main LINK_PUBLIC ${CMAKE_THREAD_LIBS_INIT} core)
set_target_properties(main PROPERTIES SUFFIX ".js" LINK_FLAGS "-s WASM=0 -s USE_PTHREADS=1 -s DEMANGLE_SUPPORT=1")
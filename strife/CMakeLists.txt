cmake_minimum_required(VERSION 3.0)
project(strife)

if(EMSCRIPTEN)
    if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake)
        include(${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake)
    endif ()
endif()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

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
execute_process(COMMAND ${CONAN_CMD} export ${CMAKE_CURRENT_SOURCE_DIR}/conan/emsdk currentproject/stable)

conan_cmake_run(CONANFILE conanfile.py
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

if(EMSCRIPTEN)
    set(CMAKE_TOOLCHAIN_FILE ${CONAN_USER_EMSDK_emscripten_root}/cmake/Modules/Platform/Emscripten.cmake)
    set(CMAKE_C_COMPILER "")
    set(CMAKE_CXX_COMPILER "")
    set(CMAKE_AR "")
    set(CMAKE_RANLIB "")

    include(${CONAN_USER_EMSDK_emscripten_root}/cmake/Modules/Platform/Emscripten.cmake)
endif()

find_package(Threads REQUIRED)
#find_package(Boost COMPONENTS system filesystem REQUIRED)

add_subdirectory(core)
add_subdirectory(project)

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

include_directories(AFTER SYSTEM
    ${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES}
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(main PROPERTIES LINK_FLAGS " -s USE_SDL=2")
else ()
    target_link_libraries(main LINK_PUBLIC
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
        ${CONAN_LIBS_SDL2}
        core
        project
    )
endif ()

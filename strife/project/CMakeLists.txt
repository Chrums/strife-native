file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)
file(GLOB_RECURSE ASSETS ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)

add_library(project ${SOURCE_FILES})
set_property(TARGET project PROPERTY CXX_STANDARD 17)

find_package(Qt5Widgets)
find_package(Qt5Core)

set(CMAKE_AUTOMOC "YES")
set(CMAKE_AUTOUIC "YES")

target_include_directories(project PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(project LINK_PUBLIC
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CONAN_LIBS}
    Qt5::Core
    Qt5::Widgets
    core
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin/)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*)

add_library(project ${SOURCE_FILES})
set_property(TARGET project PROPERTY CXX_STANDARD 17)

target_include_directories(project PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(project LINK_PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    ${CONAN_LIBS}
    core
)
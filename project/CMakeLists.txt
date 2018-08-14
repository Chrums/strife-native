file(GLOB COMPONENT_SOURCE_FILES
    assets/components/src/*
    assets/systems/src/*
)

add_library(project ${COMPONENT_SOURCE_FILES})
set_property(TARGET project PROPERTY CXX_STANDARD 17)

target_include_directories(project PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/components/include
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/systems/include
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(project LINK_PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    core
)
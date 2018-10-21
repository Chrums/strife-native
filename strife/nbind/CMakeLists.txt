

add_definitions(-DBUILDING_NODE_EXTENSION)
add_definitions(-DUSING_V8_SHARED)
add_definitions(-DUSING_UV_SHARED)
add_definitions(-DV8_DEPRECATION_WARNINGS)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
file(GLOB_RECURSE NBIND_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../node_modules/nbind/src/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/nbind/src/v8/*.cc)

add_library(nbind SHARED ${SOURCE_FILES} ${NBIND_SOURCE_FILES})

set_target_properties(nbind PROPERTIES
    PREFIX ""
    SUFFIX ".node"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out"
    )

include_directories(AFTER SYSTEM
    ${CMAKE_CURRENT_SOURCE_DIR}/../node_modules/nbind/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../node_modules/nan
    /home/michael/.cmake-js/node-x64/v10.11.0/include/node
)

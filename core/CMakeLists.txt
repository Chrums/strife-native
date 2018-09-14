file(GLOB CORE_SOURCE_FILES src/*)

add_library(core ${CORE_SOURCE_FILES})
set_property(TARGET core PROPERTY CXX_STANDARD 17)

target_include_directories(core PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/json/include
    ${Boost_INCLUDE_DIRS}
)
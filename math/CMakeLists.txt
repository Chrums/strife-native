file(GLOB CORE_SOURCE_FILES src/*)

add_library(math ${CORE_SOURCE_FILES})
set_property(TARGET math PROPERTY CXX_STANDARD 17)

target_include_directories(math PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)
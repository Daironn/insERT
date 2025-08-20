add_library(BUSINESSOBJECT BusinessObject.cpp)

target_include_directories(BUSINESSOBJECT
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/BusinessObject
)

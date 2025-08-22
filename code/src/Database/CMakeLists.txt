add_library(DATABASE Database.cpp)

target_include_directories(DATABASE
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/Database
    ${CMAKE_SOURCE_DIR}/code/include
)

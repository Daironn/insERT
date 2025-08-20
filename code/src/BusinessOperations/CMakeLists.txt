add_library(BUSINESSOPERATIONS BusinessOperations.cpp)

target_include_directories(BUSINESSOPERATIONS
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/BusinessOperations
    ${CMAKE_SOURCE_DIR}/code/include/AppUser
    ${CMAKE_SOURCE_DIR}/code/include/Document
    ${CMAKE_SOURCE_DIR}/code/include/Product
)

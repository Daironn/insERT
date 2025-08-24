add_library(PRODUCT Product.cpp)

target_include_directories(PRODUCT
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/Product
)

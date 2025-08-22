cmake_minimum_required(VERSION 3.15)
project(insERT VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(code/include)

add_subdirectory(code/src)

add_executable(insERT code/src/main.cpp)
target_link_libraries(insERT
    PRIVATE
    APP
    APPUSER
    DATABASE
    BUSINESSOPERATIONS
    DOCUMENT
    PRODUCT
)

enable_testing()
add_subdirectory(tests)

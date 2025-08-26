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
    DOCUMENT
    PRODUCT
    BUSINESSOPERATIONS
    SYSTEMOPERATIONS
)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)

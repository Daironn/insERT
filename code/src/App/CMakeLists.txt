add_library(APP App.cpp)

target_include_directories(APP
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/App
)

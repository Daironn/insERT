add_library(APP App.cpp)

target_include_directories(APP
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/App
    ${CMAKE_SOURCE_DIR}/code/include
)

target_link_libraries(APP
    PUBLIC APPUSER
    PUBLIC DATABASE
    PUBLIC PRODUCT
    PUBLIC DOCUMENT
    PUBLIC BUSINESSOPERATIONS
    )

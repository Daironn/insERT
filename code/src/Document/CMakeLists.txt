add_library(DOCUMENT Document.cpp)

target_include_directories(DOCUMENT
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/Document
)

target_link_libraries(APPUSER
    PUBLIC BUSINESSOBJECT
    PUBLIC PRODUCT
)

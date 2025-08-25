add_library(BUSINESSOPERATIONS BusinessOperations.cpp)

target_include_directories(BUSINESSOPERATIONS
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/Operations
)

target_link_libraries(BUSINESSOPERATIONS
    PUBLIC APPUSER
    PUBLIC DATABASE
    PUBLIC PRODUCT
    PUBLIC DOCUMENT
    )

add_library(SYSTEMOPERATIONS SystemOperations.cpp)

target_include_directories(SYSTEMOPERATIONS
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/Operations
)

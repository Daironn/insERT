add_library(DATABASE Database.cpp)

target_include_directories(DATABASE
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/Database    
)

target_link_libraries(DATABASE
    PUBLIC PRODUCT
    PUBLIC DOCUMENT
    PUBLIC APPUSER
    PUBLIC BUSINESSOPERATIONS
    )

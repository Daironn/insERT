add_library(APPUSER AppUser.cpp)

target_include_directories(APPUSER
    PUBLIC
    ${CMAKE_SOURCE_DIR}/code/include/AppUser
)

target_link_libraries(APPUSER
    PUBLIC BUSINESSOBJECT
)

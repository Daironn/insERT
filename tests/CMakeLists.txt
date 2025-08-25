enable_testing()

add_executable(tests_all test_all.cpp)

target_link_libraries(tests_all
    PRIVATE
    Catch2::Catch2WithMain
    gtest
    gmock
    APPUSER

)

include(CTest)
include(Catch)
catch_discover_tests(tests_all)

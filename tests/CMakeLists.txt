add_executable(tests_appuser test_appuser.cpp)

target_link_libraries(tests_appuser
    PRIVATE
    Catch2::Catch2WithMain
    gtest
    gmock
    APPUSER

)

add_executable(tests_product test_product.cpp)

target_link_libraries(tests_product
    PRIVATE
    Catch2::Catch2WithMain
    gtest
    gmock
    PRODUCT

)

add_executable(tests_document test_document.cpp)

target_link_libraries(tests_document
    PRIVATE
    Catch2::Catch2WithMain
    gtest
    gmock
    DOCUMENT

)

add_executable(tests_app test_app.cpp)

target_link_libraries(tests_app
    PRIVATE
    Catch2::Catch2WithMain
    gtest
    gmock
    APP

)

add_executable(tests_database test_database.cpp)

target_link_libraries(tests_database
    PRIVATE
    Catch2::Catch2WithMain
    gtest
    gmock
    DATABASE

)

add_executable(tests_businessoperations test_businessoperations.cpp)

target_link_libraries(tests_businessoperations
    PRIVATE
    Catch2::Catch2WithMain
    gtest
    gmock
    BUSINESSOPERATIONS

)

add_executable(tests_systemoperations test_systemoperations.cpp)

target_link_libraries(tests_systemoperations
    PRIVATE
    Catch2::Catch2WithMain
    gtest
    gmock
    SYSTEMOPERATIONS
    DOCUMENT

)

include(CTest)
include(Catch)
catch_discover_tests(tests_product)
catch_discover_tests(tests_appuser)
catch_discover_tests(tests_document)
catch_discover_tests(tests_app)
catch_discover_tests(tests_database)
catch_discover_tests(tests_businessoperations)
catch_discover_tests(tests_systemoperations)


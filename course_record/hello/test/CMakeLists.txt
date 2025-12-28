# Add test executable
add_executable(
    test
    test_main.cpp
)

target_link_libraries(
    test
    hello_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
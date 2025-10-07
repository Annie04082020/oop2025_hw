# 尋找所有測試來源檔 (.cpp)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

if(NOT TEST_SOURCES)
  message(FATAL_ERROR "No test sources found in ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
endif()

add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests PRIVATE sample_lib GTest::gtest_main)
target_compile_features(unit_tests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(unit_tests)
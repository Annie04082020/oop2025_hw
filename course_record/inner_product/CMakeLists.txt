cmake_minimum_required(VERSION 3.14)
project(inner_product LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContent for GoogleTest v1.17.0
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG    v1.17.0
)
# Prevent GoogleTest from overriding our compiler/linker options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add source files (if any)
file(GLOB_RECURSE INNER_PRODUCT_SRC src/*.cpp)
add_library(inner_product_lib ${INNER_PRODUCT_SRC})

# Add test files
file(GLOB_RECURSE INNER_PRODUCT_TESTS tests/*.cpp)

add_executable(inner_product_tests ${INNER_PRODUCT_TESTS})
target_link_libraries(inner_product_tests PRIVATE inner_product_lib gtest_main)

target_include_directories(inner_product_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(inner_product_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_test(NAME DummyTest COMMAND inner_product_tests)

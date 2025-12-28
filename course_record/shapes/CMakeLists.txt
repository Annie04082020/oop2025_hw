
cmake_minimum_required(VERSION 3.14)
project(shapes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if googletest source directory already exists
set(GOOGLETEST_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/googletest-src")

if(EXISTS "${GOOGLETEST_SOURCE_DIR}" AND IS_DIRECTORY "${GOOGLETEST_SOURCE_DIR}")
    message(STATUS "Google Test already exists at ${GOOGLETEST_SOURCE_DIR}, skipping download")
    set(FETCHCONTENT_FULLY_DISCONNECTED ON)
else()
    message(STATUS "Google Test not found, will download to ${GOOGLETEST_SOURCE_DIR}")
    set(FETCHCONTENT_FULLY_DISCONNECTED OFF)
endif()

# FetchContent for GoogleTest v1.17.0
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG    v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add source files as a library
file(GLOB_RECURSE SHAPES_SRC src/*.cpp)
add_library(shapes_lib ${SHAPES_SRC})
target_include_directories(shapes_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add dummy_test
add_executable(dummy_test tests/dummy_test.cpp)
target_link_libraries(dummy_test gtest_main)
add_test(NAME DummyTest COMMAND dummy_test)

# Add shape_test
add_executable(shape_test tests/shape_test.cpp)
target_link_libraries(shape_test shapes_lib gtest_main)
target_include_directories(shape_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_test(NAME ShapeTest COMMAND shape_test)

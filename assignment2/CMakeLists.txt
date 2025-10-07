cmake_minimum_required(VERSION 3.16)
project(sample_code CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include CTest
enable_testing()

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Add test files
file(GLOB_RECURSE UNIT_TESTS tests/*.cpp)

add_executable(unit_tests ${UNIT_TESTS} ${SOURCES})
target_link_libraries(unit_tests PRIVATE gtest_main)
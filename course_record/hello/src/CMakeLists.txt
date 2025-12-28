# Create a library for our sample code
add_library(
    hello_lib
    INTERFACE
)

target_include_directories(hello_lib INTERFACE src/)

# Add main executable
add_executable(
    hello
    hello.cpp
)

target_link_libraries(
    hello
    hello_lib
)

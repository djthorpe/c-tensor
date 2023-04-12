cmake_minimum_required (VERSION 3.0)
project(tensor VERSION 0.0.1)

# Libraries
add_subdirectory(src/tensor)
add_subdirectory(src/string)
add_subdirectory(src/math)

# Unit Tests
add_subdirectory(tests/tensor)
add_subdirectory(tests/string)
add_subdirectory(tests/math)

# Examples
add_subdirectory(examples/main)
add_subdirectory(examples/names)
add_subdirectory(examples/xor)

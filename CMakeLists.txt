cmake_minimum_required (VERSION 3.0)
project(tensor VERSION 0.0.1)

# Libraries
add_subdirectory(src/base)
add_subdirectory(src/math)
add_subdirectory(src/string)
add_subdirectory(src/tensor)

# Unit Tests
add_subdirectory(tests/base)
add_subdirectory(tests/math)
add_subdirectory(tests/string)
add_subdirectory(tests/tensor)

# Examples
add_subdirectory(examples/main)
add_subdirectory(examples/names)
add_subdirectory(examples/xor)

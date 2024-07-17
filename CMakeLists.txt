cmake_minimum_required (VERSION 3.5)
project(tensor VERSION 0.0.1)

# Libraries
add_subdirectory(src/tensor)

# Tests
include(CTest)
add_subdirectory(tests/base_001)

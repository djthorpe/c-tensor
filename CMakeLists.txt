cmake_minimum_required (VERSION 3.0)
project(tensor VERSION 0.0.1)

# Libraries
add_subdirectory(src/tensor)
add_subdirectory(src/csv)

# Unit Tests
add_subdirectory(test/tensor)

# Examples
add_subdirectory(examples/main)
add_subdirectory(examples/names)

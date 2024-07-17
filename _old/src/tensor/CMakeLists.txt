add_library(tensor_tensor STATIC
    cast.c
    graph.c
    mul.c
    scalar.c
    tensor.c
    vector.c
)

target_include_directories(tensor_tensor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/..
)

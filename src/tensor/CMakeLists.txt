add_library(tensor STATIC
    cast.c
    graph.c
    hashmap.c
    mul.c
    pool.c
    scalar.c
    tensor.c
    vector.c
)

target_include_directories(tensor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/..
)

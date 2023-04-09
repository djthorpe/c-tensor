add_library(tensor STATIC
    cast.c
    mul.c
    pool.c
    string.c
    tensor.c
)

target_include_directories(tensor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

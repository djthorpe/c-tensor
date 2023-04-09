add_library(tensor STATIC
    pool.c
    tensor.c
    string.c
)

target_include_directories(tensor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

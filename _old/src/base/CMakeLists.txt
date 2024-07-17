add_library(tensor_base STATIC
    debug.c
    hashmap.c
    pool.c
)

target_include_directories(tensor_base PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/..
)

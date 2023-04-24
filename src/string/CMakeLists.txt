add_library(tensor_string STATIC
    args.c
    csv.c
    hash.c
    hashmap.c
    string.c
    tensor.c
    token.c
)

target_include_directories(tensor_string PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(tensor_string
    tensor_base
)

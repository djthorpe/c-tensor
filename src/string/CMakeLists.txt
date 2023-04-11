add_library(tensor_string STATIC
    string.c
    token.c
)

target_include_directories(tensor_string PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/..
)

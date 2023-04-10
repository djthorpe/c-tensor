add_library(tensor_csv STATIC
    csv.c
)

target_include_directories(tensor_csv PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

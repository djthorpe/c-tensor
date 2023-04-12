add_library(tensor_math STATIC
    rand.c
)

target_include_directories(tensor_math PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(tensor_math m)

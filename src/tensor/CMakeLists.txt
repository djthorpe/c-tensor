add_library(tensor STATIC
    mat_f32/mat_f32.c
    mat_f32/mat_f32_write.c
)
target_include_directories(tensor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

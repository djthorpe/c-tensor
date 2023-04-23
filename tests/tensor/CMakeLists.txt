add_executable(test_tensor
    main.c
    tensor.c
    scalar.c
    vector.c
)

target_include_directories(test_tensor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(test_tensor 
    tensor_base
    tensor_string
    tensor_tensor
)

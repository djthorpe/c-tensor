add_executable(test_string
    args.c
    csv.c
    main.c
    string.c
    tensor.c
    token.c
)

target_include_directories(test_string PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(test_string 
    tensor_base
    tensor_string
    tensor_tensor
)


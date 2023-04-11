add_executable(test_tensor
    csv.c
    main.c
    pool.c
    scalar.c
)

target_include_directories(test_tensor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(test_tensor 
    tensor
    tensor_string
)

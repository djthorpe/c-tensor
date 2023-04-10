add_executable(test_tensor
    main.c
    pool.c
)

target_include_directories(test_tensor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

target_link_libraries(test_tensor 
    tensor
)

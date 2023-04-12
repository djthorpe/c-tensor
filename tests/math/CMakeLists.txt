add_executable(test_math
    main.c
    rand.c
)

target_include_directories(test_string PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(test_math 
    tensor
    tensor_math
)

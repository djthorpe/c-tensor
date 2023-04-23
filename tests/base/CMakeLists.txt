add_executable(test_base
    hashmap.c
    main.c
    pool.c
)

target_include_directories(test_base PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
    ${CMAKE_CURRENT_LIST_DIR}/../../src
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(test_base 
    tensor_base
)

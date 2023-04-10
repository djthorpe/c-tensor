add_executable(names 
    main.c
)

target_include_directories(names PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

target_link_libraries(names 
    tensor
    tensor_csv
)

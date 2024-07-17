add_executable(xor 
    main.c
)

target_include_directories(xor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

target_link_libraries(xor 
    tensor
)

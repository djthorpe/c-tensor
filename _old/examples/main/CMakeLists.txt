add_executable(main 
    main.c
)

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

target_link_libraries(main 
    tensor
)

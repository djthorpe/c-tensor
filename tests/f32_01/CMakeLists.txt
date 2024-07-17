set(NAME "f32_01")

add_executable(${NAME}
    main.c
)
target_include_directories(${NAME} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)
target_link_libraries(${NAME} 
    tensor
)

add_test(NAME ${NAME} COMMAND ${NAME})

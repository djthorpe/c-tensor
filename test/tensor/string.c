#include <stdio.h>

#include <tensor/tensor.h>
#include "test.h"

void test_string_000()
{
    printf("Running test_string_000\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    // Create a string using printf
    tensor_str_t *str = tensor_str_printf(pool, "Hello %s", "World");
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS(11, tensor_str_len(str));
    ASSERT_EQUALS_STR("Hello World", tensor_cstring(str));

    tensor_pool_destroy(pool);
}

void test_string_001()
{
    printf("Running test_string_001\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    // Concatenate two strings
    tensor_str_t *str1 = tensor_str_create(pool, "Hello ");
    ASSERT_NOTNULL(str1);

    tensor_str_t *str2 = tensor_str_create(pool, "World");
    ASSERT_NOTNULL(str2);

    // Concatenate
    tensor_str_t *str3 = tensor_str_concat(pool, str1, str2);
    ASSERT_NOTNULL(str3);
    ASSERT_EQUALS(str3, str1);

    tensor_pool_destroy(pool);
}

void test_string_002()
{
    printf("Running test_string_002\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_pool_destroy(pool);
}

void test_string()
{
    test_string_000();
    test_string_001();
    test_string_002();
}

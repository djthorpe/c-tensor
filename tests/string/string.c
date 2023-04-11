#include <stdio.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "test.h"

void test_string_000()
{
    printf("Running test_string_000 (tensor_str_create)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    // Create 10 empty strings
    for (int i = 0; i < 10; i++)
    {
        tensor_str_t *str = tensor_str_create(pool, NULL);
        ASSERT_NOTNULL(str);
        ASSERT_EQUALS(0, tensor_str_len(str));
    }

    tensor_pool_destroy(pool);
}

void test_string_001()
{
    printf("Running test_string_001 (tensor_str_create, tensor_str_len)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    // Create 10 strings
    for (int i = 0; i < 10; i++)
    {
        tensor_str_t *str = tensor_str_create(pool, "Hello, world");
        ASSERT_NOTNULL(str);
        ASSERT_EQUALS(12, tensor_str_len(str));

        // Zero the string
        tensor_str_zero(str);
        ASSERT_EQUALS(0, tensor_str_len(str));
    }

    tensor_pool_destroy(pool);
}

void test_string_002()
{
    printf("Running test_string_002 (tensor_str_create)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    // Create an empty string and concatenate 10 strings
    tensor_str_t *str = tensor_str_create(pool, NULL);
    ASSERT_NOTNULL(str);
    for (int i = 1; i < 10; i++)
    {
        tensor_str_t *a = tensor_str_create(pool, "X");
        ASSERT_NOTNULL(str);
        bool success = tensor_str_concat(str, a);
        ASSERT(success);

        ASSERT_EQUALS(i, tensor_str_len(str));
    }
    printf("  string=%s\n", tensor_cstring(str));

    tensor_pool_destroy(pool);
}

void test_string_003()
{
    printf("Running test_string_003 (tensor_str_printf)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    // Create an empty string and concatenate 10 strings
    tensor_str_t *str = tensor_str_create(pool, NULL);
    ASSERT_NOTNULL(str);
    for (int i = 1; i < 10; i++)
    {
        bool success = tensor_str_printf(str, "%d ", i);
        ASSERT(success);
        ASSERT_EQUALS(i * 2, tensor_str_len(str));
        printf("  string=%s len=%lu\n", tensor_cstring(str), tensor_str_len(str));
    }
    tensor_pool_destroy(pool);
}

void test_string()
{
    test_string_000();
    test_string_001();
    test_string_002();
    test_string_003();
}

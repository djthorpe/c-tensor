#include <stdio.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "test.h"

void test_token_000()
{
    printf("Running test_token_000\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_str_t *str = tensor_str_create(pool, "Hello, world");
    ASSERT(str);
    tensor_str_token_t *token = tensor_str_tokenize(pool, str, "H ", true, NULL);
    ASSERT(token);

    tensor_pool_destroy(pool);
}

void test_token()
{
    test_token_000();
}

#include <stdio.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "test.h"

#define buf_size 80
static char buf[buf_size];

void test_tensor_000()
{
    printf("Running test_tensor_000\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar = tensor_create(pool, UINT32_T, NULL);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_describe(pool, scalar);
    ASSERT_NOTNULL(str);
    printf("  tensor_str_describe=%s\n", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor()
{
    test_tensor_000();
}

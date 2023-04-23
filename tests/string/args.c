#include <stdio.h>

#include <tensor/base.h>
#include <tensor/string.h>
#include <tensor/tensor.h>
#include "test.h"

#define buf_size 80
static char buf[buf_size];

void test_args_000()
{
    printf("Running test_args_000\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT_NOTNULL(pool);

    tensor_str_args_t *args = tensor_str_args_create(pool, 3, (const char *[]){"Hello, world", "arg1", "arg2"});
    ASSERT(args);

    tensor_pool_destroy(pool);
}

void test_args()
{
    test_args_000();
}

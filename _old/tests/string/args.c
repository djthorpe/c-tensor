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
    ASSERT(pool);

    tensor_str_args_t *args = tensor_str_args_create(pool, 9, (const char *[]){"/name/of/command", "-test1", "value1", "--test2", "value2", "--test3", "-", "arg1", "arg2"});
    ASSERT(args);

    ASSERT(tensor_str_args_flag(args, "test1", "A string flag", NULL));
    ASSERT(tensor_str_args_flag(args, "test2", "A string flag", NULL));
    ASSERT(tensor_str_args_switch(args, "test3", "A switch flag"));
    ASSERT(tensor_str_args_parse(args));

    tensor_pool_destroy(pool);
}

void test_args()
{
    test_args_000();
}

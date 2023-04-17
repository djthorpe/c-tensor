#include <stdio.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "test.h"

#define buf_size 80
static char buf[buf_size];
static const char *lorem_ipsum = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";
static const char *csv = "apple, banana,  corange,  \tdamon,\t\t pear,\t\t\n";

void test_token_000()
{
    printf("Running test_token_000\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT_NOTNULL(pool);

    tensor_str_t *str = tensor_str_create(pool, (char* )lorem_ipsum);
    ASSERT(str);
    tensor_str_token_t *token = tensor_str_tokenize(pool, str, " ,.", true, NULL);
    ASSERT(token);

    while (token)
    {
        printf("  token=%s\n", tensor_cstring(buf, buf_size, tensor_str_token_describe(pool, token)));
        token = tensor_str_token_next(token);
    }

    tensor_pool_destroy(pool);
}

void test_token_001()
{
    printf("Running test_token_001\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT_NOTNULL(pool);

    tensor_str_t *str = tensor_str_create(pool, (char* )csv);
    ASSERT(str);
    tensor_str_token_t *token = tensor_str_tokenize(pool, str, ",", true, NULL);
    ASSERT(token);

    while (token)
    {
        printf("  token=%s\n", tensor_cstring(buf, buf_size, tensor_str_token_describe(pool, token)));
        token = tensor_str_token_next(token);
    }

    tensor_pool_destroy(pool);
}

void test_token()
{
    test_token_000();
    test_token_001();
}

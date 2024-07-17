#include <stdio.h>

#include <tensor/base.h>
#include <tensor/string.h>
#include <tensor/tensor.h>
#include "test.h"

#define buf_size 80
static char buf[buf_size];

void test_hash_000()
{
    printf("Running test_hash_000\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT(pool);

    tensor_str_t *str1 = tensor_str_create(pool, "Hello, world!\n");
    ASSERT(str1);
    debug("  str1: %s hash: %zu\n", tensor_cstring(buf, buf_size, str1), tensor_str_hash(str1));

    tensor_str_t *str2 = tensor_str_create(pool, "Hello, world!\n");
    ASSERT(str2);
    debug("  str2: %s hash: %zu\n", tensor_cstring(buf, buf_size, str2), tensor_str_hash(str2));

    ASSERT_EQUALS(tensor_str_hash(str1), tensor_str_hash(str2));

    tensor_pool_destroy(pool);
}

void test_hash_001()
{
    printf("Running test_hash_001\n");
 
    // Empty string and zero-sized string are the same
    // and the hash is always zero
 
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT(pool);

    tensor_str_t *str1 = tensor_str_create(pool, "");
    ASSERT(str1);
    debug("  str1: %s hash: %zu\n", tensor_cstring(buf, buf_size, str1), tensor_str_hash(str1));

    tensor_str_t *str2 = tensor_str_create(pool, NULL);
    ASSERT(str2);
    debug("  str2: %s hash: %zu\n", tensor_cstring(buf, buf_size, str2), tensor_str_hash(str2));

    ASSERT_EQUALS(0, tensor_str_hash(str1));
    ASSERT_EQUALS(0, tensor_str_hash(str2));

    tensor_pool_destroy(pool);
}

void test_hash()
{
    test_hash_000();
    test_hash_001();
}

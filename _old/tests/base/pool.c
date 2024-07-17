#include <stdio.h>
#include <tensor/base.h>
#include "test.h"

void test_pool_000()
{
    printf("Running test_pool_000\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);
    ASSERT_EQUALS(1024, tensor_pool_size(pool));
    ASSERT_EQUALS(0, tensor_pool_used(pool));
    tensor_pool_destroy(pool);
}

void test_pool_001()
{
    printf("Running test_pool_001\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    // Allocate a 1024 byte block
    void *ptr1 = tensor_pool_alloc(pool, 1024, NULL);
    ASSERT_NOTNULL(ptr1);

    // Allocate a 1024 byte block - should fail
    void *ptr2 = tensor_pool_alloc(pool, 1024, NULL);
    ASSERT_NULL(ptr2);

    tensor_pool_destroy(pool);
}

void test_pool_002()
{
    printf("Running test_pool_002\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    // Allocate 128 1-byte blocks - blocks align on 64 bit (8 byte) boundaries
    for(int i = 0; i < 128; i++)
    {
        void *ptr = tensor_pool_alloc(pool, 1, NULL);
        ASSERT_NOTNULL(ptr);
    }

    // Used bytes is 1024
    ASSERT_EQUALS(1024, tensor_pool_used(pool));

    tensor_pool_destroy(pool);
}

void test_pool()
{
    test_pool_000();
    test_pool_001();
    test_pool_002();
}

#include <stdio.h>

#include <tensor/base.h>
#include "test.h"

void test_hashmap_000()
{
    printf("Running test_hashmap_000\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_hashmap_t *hashmap = tensor_hashmap_create(pool, 10);
    ASSERT_NOTNULL(hashmap);

    for (size_t i = 1; i < 100; i++)
    {
        bool success = tensor_hashmap_put(hashmap, (void *)i, (void *)i);
        if (!success && i <= 10)
        {
            debug("tensor_hashmap_put: failed to put %d\n", i);
        }
    }

    for (size_t i = 1; i < 10; i++)
    {
        size_t value = (size_t)tensor_hashmap_get(hashmap, (void *)i);
        ASSERT_EQUALS(value, i);
    }

    tensor_pool_destroy(pool);
}

void test_hashmap_001()
{
    printf("Running test_hashmap_001\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT_NOTNULL(pool);

    tensor_hashmap_t *hashmap = tensor_hashmap_create(pool, 200);
    ASSERT_NOTNULL(hashmap);

    for (size_t i = 1; i < 100; i++)
    {
        static char buf[80];
        sprintf(buf, "Hello, world %lu", i);
        bool success = tensor_hashmap_put_cstring(hashmap, pool, buf, (void *)i);
        if (!success && i <= 10)
        {
            debug("tensor_hashmap_put_cstring: failed to put %s\n", buf);
        }
    }

    for (size_t i = 1; i < 100; i++)
    {
        static char buf[80];
        sprintf(buf, "Hello, world %lu", i);
        size_t value = (size_t)tensor_hashmap_get_cstring(hashmap, buf);
        ASSERT_EQUALS(value, i);
    }

    tensor_pool_destroy(pool);
}

void test_hashmap()
{
    test_hashmap_000();
    test_hashmap_001();
}

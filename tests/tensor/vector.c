#include <stdio.h>

#include <tensor/tensor.h>
#include "test.h"

void test_vector_000()
{
    printf("Running test_vector_000 (create int32 vector)\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT_NOTNULL(pool);

    // Create a 10-element vector of dtype int32
    tensor_t *vector_int32 = tensor_int32_vec(pool, 10, (int32_t[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    ASSERT(vector_int32);
    ASSERT(!tensor_is_scalar(vector_int32));
    ASSERT(tensor_is_vector(vector_int32));

    tensor_pool_destroy(pool);
}

void test_vector_001()
{
    printf("Running test_vector_001 (create uint32 vector)\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT_NOTNULL(pool);

    // Create a 10-element vector of dtype uint32
    tensor_t *vector_uint32 = tensor_uint32_vec(pool, 10, NULL);
    ASSERT(vector_uint32);
    ASSERT(!tensor_is_scalar(vector_uint32));
    ASSERT(tensor_is_vector(vector_uint32));

    tensor_pool_destroy(pool);
}

void test_vector_002()
{
    printf("Running test_vector_002 (create int64 vector)\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT_NOTNULL(pool);

    // Create a 10-element vector of dtype int64
    tensor_t *vector_int64 = tensor_int64_vec(pool, 10, (int64_t[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    ASSERT(vector_int64);
    ASSERT(!tensor_is_scalar(vector_int64));
    ASSERT(tensor_is_vector(vector_int64));

    tensor_pool_destroy(pool);
}

void test_vector_003()
{
    printf("Running test_vector_003 (create uint64 vector)\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT_NOTNULL(pool);

    // Create a 10-element vector of dtype uint64
    tensor_t *vector_uint64 = tensor_uint64_vec(pool, 10, (uint64_t[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    ASSERT(vector_uint64);
    ASSERT(!tensor_is_scalar(vector_uint64));
    ASSERT(tensor_is_vector(vector_uint64));

    tensor_pool_destroy(pool);
}

void test_vector_004()
{
    printf("Running test_vector_004 (create float32 vector)\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT_NOTNULL(pool);

    // Create a 10-element vector of dtype float32
    tensor_t *vector_float32 = tensor_float32_vec(pool, 10, (float[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    ASSERT(vector_float32);
    ASSERT(!tensor_is_scalar(vector_float32));
    ASSERT(tensor_is_vector(vector_float32));

    tensor_pool_destroy(pool);
}

void test_vector_005()
{
    printf("Running test_vector_005 (create float64 vector)\n");
    tensor_pool_t *pool = tensor_pool_create(64 * 1024);
    ASSERT_NOTNULL(pool);

    // Create a 10-element vector of dtype float64
    tensor_t *vector_float64 = tensor_float64_vec(pool, 10, NULL);
    ASSERT(vector_float64);
    ASSERT(!tensor_is_scalar(vector_float64));
    ASSERT(tensor_is_vector(vector_float64));

    tensor_pool_destroy(pool);
}

void test_vector()
{
    test_vector_000();
    test_vector_001();
    test_vector_002();
    test_vector_003();
    test_vector_004();
    test_vector_005();
}

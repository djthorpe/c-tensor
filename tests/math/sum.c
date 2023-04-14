#include <stdio.h>
#include <limits.h>

#include <tensor/tensor.h>
#include <tensor/math.h>
#include "tensor_private.h"
#include "test.h"

void test_sum_000()
{
    printf("Running test_sum_000 (int32)\n");

    tensor_pool_t *pool = tensor_pool_create(1024);
    bool overflow = false;

    int32_t sum = tensor_math_sum_int32_vec(2, (int32_t[]){0, 0}, &overflow);
    ASSERT(sum == 0);
    ASSERT(!overflow);

    overflow = false;
    tensor_math_sum_int32_vec(2, (int32_t[]){INT32_MAX, 1}, &overflow);
    ASSERT(overflow);

    overflow = false;
    tensor_math_sum_int32_vec(2, (int32_t[]){1, INT32_MAX}, &overflow);
    ASSERT(overflow);

    overflow = false;
    tensor_math_sum_int32_vec(2, (int32_t[]){-1, INT32_MIN}, &overflow);
    ASSERT(overflow);

    overflow = false;
    tensor_math_sum_int32_vec(2, (int32_t[]){INT32_MIN, -1}, &overflow);
    ASSERT(overflow);

    tensor_pool_destroy(pool);
}

void test_sum_001()
{
    printf("Running test_sum_001 (uint32)\n");

    tensor_pool_t *pool = tensor_pool_create(1024);
    bool overflow = false;

    int32_t sum = tensor_math_sum_uint32_vec(2, (uint32_t[]){1, 2}, &overflow);
    ASSERT(sum == 3);
    ASSERT(!overflow);

    overflow = false;
    tensor_math_sum_uint32_vec(2, (uint32_t[]){UINT32_MAX, 1}, &overflow);
    ASSERT(overflow);

    overflow = false;
    tensor_math_sum_uint32_vec(2, (uint32_t[]){1, UINT32_MAX}, &overflow);
    ASSERT(overflow);

    tensor_pool_destroy(pool);
}

void test_sum_002()
{
    printf("Running test_sum_002 (int64)\n");

    tensor_pool_t *pool = tensor_pool_create(1024);
    bool overflow = false;

    int64_t sum = tensor_math_sum_int64_vec(3, (int64_t[]){4, 5, 6}, &overflow);
    ASSERT(sum == 15);
    ASSERT(!overflow);

    overflow = false;
    tensor_math_sum_int64_vec(2, (int64_t[]){INT64_MAX, 1}, &overflow);
    ASSERT(overflow);

    overflow = false;
    tensor_math_sum_int64_vec(2, (int64_t[]){INT64_MIN, -1}, &overflow);
    ASSERT(overflow);

    tensor_pool_destroy(pool);
}

void test_sum_003()
{
    printf("Running test_sum_003 (uint64)\n");

    tensor_pool_t *pool = tensor_pool_create(1024);
    bool overflow = false;

    uint64_t sum = tensor_math_sum_uint64_vec(4, (uint64_t[]){4, 5, 6, 7}, &overflow);
    ASSERT(sum == 22);
    ASSERT(!overflow);

    overflow = false;
    tensor_math_sum_uint64_vec(2, (uint64_t[]){UINT64_MAX, 1}, &overflow);
    ASSERT(overflow);

    tensor_pool_destroy(pool);
}

void test_sum()
{
    test_sum_000();
    test_sum_001();
    test_sum_002();
    test_sum_003();
}

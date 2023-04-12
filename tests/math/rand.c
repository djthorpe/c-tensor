#include <stdio.h>
#include <limits.h>

#include <tensor/tensor.h>
#include <tensor/math.h>
#include "test.h"

void test_rand_000()
{
    printf("Running test_rand_000 (tensor_math_rand_uint64)\n");

    tensor_pool_t *pool = tensor_pool_create(1024);
    tensor_math_rand_generator_t *generator = tensor_math_rand_generator_create(pool, 1);
    for (int i = 0; i < 100; i++)
    {
        uint64_t value = tensor_math_rand_uint64(generator);
        assert(value >= 0 && value <= UINT64_MAX);
        printf("value = %llu\n", value);
    }
    tensor_pool_destroy(pool);
}

void test_rand_001()
{
    printf("Running test_rand_001 (tensor_math_rand_int63)\n");

    tensor_pool_t *pool = tensor_pool_create(1024);
    tensor_math_rand_generator_t *generator = tensor_math_rand_generator_create(pool, 1);
    for (int i = 0; i < 100; i++)
    {
        int64_t value = tensor_math_rand_int63(generator);
        assert(value >= 0 && value <= INT64_MAX);
        printf("value = %lld\n", value);
    }
    tensor_pool_destroy(pool);
}

void test_rand_002()
{
    printf("Running test_rand_002(tensor_math_rand_float64)\n");

    tensor_pool_t *pool = tensor_pool_create(1024);
    tensor_math_rand_generator_t *generator = tensor_math_rand_generator_create(pool, 1);
    for (int i = 0; i < 100; i++)
    {
        double value = tensor_math_rand_float64(generator);
        printf("value = %f\n", value);
    }
    tensor_pool_destroy(pool);
}

void test_rand_003()
{
    printf("Running test_rand_003(tensor_math_randn_float64)\n");

    tensor_pool_t *pool = tensor_pool_create(1024);
    tensor_math_rand_generator_t *generator = tensor_math_rand_generator_create(pool, 1);
    for (int i = 0; i < 100; i++)
    {
        double value = tensor_math_randn_float64(generator, 0.0, 1.0);
        printf("value = %f\n", value);
    }
    tensor_pool_destroy(pool);
}

void test_rand()
{
    test_rand_000();
    test_rand_001();
    test_rand_002();
    test_rand_003();
}

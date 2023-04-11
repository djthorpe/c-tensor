#include <stdio.h>

#include <tensor/tensor.h>
#include "test.h"

void test_scalar_000()
{
    printf("Running test_scalar_000 (create scalar)\n");
    tensor_pool_t *pool = tensor_pool_create(2 * 1024);
    ASSERT_NOTNULL(pool);

    // int32
    tensor_t *scalar_int32 = tensor_int32(pool, 123);
    ASSERT(scalar_int32);
    ASSERT(tensor_is_scalar(scalar_int32));
    ASSERT_EQUALS(123, tensor_int32_value(scalar_int32));

    // uint32
    tensor_t *scalar_uint32 = tensor_uint32(pool, 456);
    ASSERT(scalar_uint32);
    ASSERT(tensor_is_scalar(scalar_uint32));
    ASSERT_EQUALS(456, tensor_uint32_value(scalar_uint32));

    // int64
    tensor_t *scalar_int64 = tensor_int64(pool, 789);
    ASSERT(scalar_int64);
    ASSERT(tensor_is_scalar(scalar_int64));
    ASSERT_EQUALS(789, tensor_int64_value(scalar_int64));

    // uint64
    tensor_t *scalar_uint64 = tensor_uint64(pool, 101112);
    ASSERT(scalar_uint64);
    ASSERT(tensor_is_scalar(scalar_uint64));
    ASSERT_EQUALS(101112, tensor_uint64_value(scalar_uint64));

    // float32
    tensor_t *scalar_float32 = tensor_float32(pool, 131415);
    ASSERT(scalar_float32);
    ASSERT(tensor_is_scalar(scalar_float32));
    ASSERT_EQUALS(131415, tensor_float32_value(scalar_float32));

    // float64
    tensor_t *scalar_float64 = tensor_float64(pool, 161718);
    ASSERT(scalar_float64);
    ASSERT(tensor_is_scalar(scalar_float64));
    ASSERT_EQUALS(161718, tensor_float64_value(scalar_float64));

    tensor_pool_destroy(pool);
}

void test_scalar_001()
{
    printf("Running test_scalar_001 (int32 cast)\n");

    tensor_pool_t *pool = tensor_pool_create(2 * 1024);
    ASSERT_NOTNULL(pool);

    // cast int32 -> uint32
    tensor_t *scalar_int32 = tensor_int32(pool, 123);
    ASSERT(scalar_int32);

    tensor_t *scalar_uint32 = tensor_cast(pool, UINT32_T, scalar_int32);
    ASSERT(scalar_uint32);

    tensor_t *scalar_int64 = tensor_cast(pool, INT64_T, scalar_uint32);
    ASSERT(scalar_int64);

    tensor_t *scalar_uint64 = tensor_cast(pool, UINT64_T, scalar_int64);
    ASSERT(scalar_uint64);

    tensor_t *scalar_float32 = tensor_cast(pool, FLOAT32_T, scalar_uint64);
    ASSERT(scalar_float32);

    tensor_t *scalar_float64 = tensor_cast(pool, FLOAT64_T, scalar_float32);
    ASSERT(scalar_float64);

    // Run graph on output node
    tensor_graph_t *graph = tensor_graph_create(pool, scalar_float64);
    ASSERT_NOTNULL(graph);
    tensor_t *output = tensor_graph_evaluate(graph);
    ASSERT_NOTNULL(output);

    // Check cast operation output
    ASSERT_EQUALS(123, tensor_float64_value(output));

    tensor_pool_destroy(pool);
}

void test_scalar()
{
    test_scalar_000();
    test_scalar_001();
}

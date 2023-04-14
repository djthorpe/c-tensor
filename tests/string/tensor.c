#include <stdio.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "test.h"

#define buf_size 80
static char buf[buf_size];

void test_tensor_000()
{
    printf("Running test_tensor_000 (int32)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar = tensor_int32(pool, 1234);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_describe(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT(tensor_str_has_prefix(str, "scalar["));
    ASSERT(tensor_str_has_suffix(str, "=int32]"));
    printf("  tensor_str_describe=%s\n", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_001()
{
    printf("Running test_tensor_001 (uint32)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar = tensor_uint32(pool, 5678);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_describe(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT(tensor_str_has_prefix(str, "scalar["));
    ASSERT(tensor_str_has_suffix(str, "=uint32]"));
    printf("  tensor_str_describe=%s\n", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_002()
{
    printf("Running test_tensor_002 (int64)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar = tensor_int64(pool, 1234);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_describe(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT(tensor_str_has_prefix(str, "scalar["));
    ASSERT(tensor_str_has_suffix(str, "=int64]"));
    printf("  tensor_str_describe=%s\n", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_003()
{
    printf("Running test_tensor_003 (uint64)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar = tensor_uint64(pool, 5678);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_describe(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT(tensor_str_has_prefix(str, "scalar["));
    ASSERT(tensor_str_has_suffix(str, "=uint64]"));
    printf("  tensor_str_describe=%s\n", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_004()
{
    printf("Running test_tensor_004 (float32)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar = tensor_float32(pool, 12.34);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_describe(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT(tensor_str_has_prefix(str, "scalar["));
    ASSERT(tensor_str_has_suffix(str, "=float32]"));
    printf("  tensor_str_describe=%s\n", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_005()
{
    printf("Running test_tensor_005 (float64)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar = tensor_float64(pool, 56.78);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_describe(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT(tensor_str_has_prefix(str, "scalar["));
    ASSERT(tensor_str_has_suffix(str, "=float64]"));
    printf("  tensor_str_describe=%s\n", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_010()
{
    printf("Running test_tensor_010 (vector int32)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *vector = tensor_int32_vec(pool, 4, (int32_t[]){12, 34, 56, 78});
    ASSERT_NOTNULL(vector);

    tensor_str_t *str = tensor_str_describe(pool, vector);
    ASSERT_NOTNULL(str);
    ASSERT(tensor_str_has_prefix(str, "vector["));
    ASSERT(tensor_str_has_suffix(str, "=int32]"));
    printf("  tensor_str_describe=%s\n", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor()
{
    // Scalars
    test_tensor_000();
    test_tensor_001();
    test_tensor_002();
    test_tensor_003();
    test_tensor_004();
    test_tensor_005();

    // Vectors
    test_tensor_010();
}

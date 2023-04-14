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

void test_tensor_020()
{
    printf("Running test_tensor_020 (vector int32 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *vector = tensor_int32_vec(pool, 4, (int32_t[]){12, -34, 56, -78});
    ASSERT_NOTNULL(vector);

    tensor_str_t *str = tensor_str_print(pool, vector);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("[12,-34,56,-78]", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_021()
{
    printf("Running test_tensor_021 (vector uint32 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *vector = tensor_uint32_vec(pool, 4, (uint32_t[]){12, 34, 56, 78});
    ASSERT_NOTNULL(vector);

    tensor_str_t *str = tensor_str_print(pool, vector);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("[12,34,56,78]", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_022()
{
    printf("Running test_tensor_022 (vector int64 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *vector = tensor_int64_vec(pool, 4, (int64_t[]){12, -34, 56, -78});
    ASSERT_NOTNULL(vector);

    tensor_str_t *str = tensor_str_print(pool, vector);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("[12,-34,56,-78]", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_023()
{
    printf("Running test_tensor_023 (vector uint64 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *vector = tensor_uint64_vec(pool, 4, (uint64_t[]){12, 34, 56, 78});
    ASSERT_NOTNULL(vector);

    tensor_str_t *str = tensor_str_print(pool, vector);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("[12,34,56,78]", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_024()
{
    printf("Running test_tensor_024 (vector float32 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *vector = tensor_float32_vec(pool, 4, (float[]){1.2, 3.4, 5.6, 7.8});
    ASSERT_NOTNULL(vector);

    tensor_str_t *str = tensor_str_print(pool, vector);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("[1.2000,3.4000,5.6000,7.8000]", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_025()
{
    printf("Running test_tensor_025 (vector float64 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *vector = tensor_float64_vec(pool, 4, (double[]){1.2, 3.4, 5.6, 7.8});
    ASSERT_NOTNULL(vector);

    tensor_str_t *str = tensor_str_print(pool, vector);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("[1.2000,3.4000,5.6000,7.8000]", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_030()
{
    printf("Running test_tensor_030 (scalar int32 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar= tensor_int32(pool, -78);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_print(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("-78", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_031()
{
    printf("Running test_tensor_031 (scalar uint32 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar= tensor_uint32(pool, 78);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_print(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("78", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_032()
{
    printf("Running test_tensor_032 (scalar int64 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar= tensor_int64(pool, -78910);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_print(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("-78910", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_033()
{
    printf("Running test_tensor_033 (scalar uint64 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar= tensor_uint64(pool, 123456789);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_print(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("123456789", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_034()
{
    printf("Running test_tensor_034 (scalar float32 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar= tensor_float32(pool, -3.1415);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_print(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("-3.1415", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor_035()
{
    printf("Running test_tensor_035 (scalar float64 print)\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_t *scalar= tensor_float64(pool, 3.1415);
    ASSERT_NOTNULL(scalar);

    tensor_str_t *str = tensor_str_print(pool, scalar);
    ASSERT_NOTNULL(str);
    ASSERT_EQUALS_STR("3.1415", tensor_cstring(buf, buf_size, str));

    tensor_pool_destroy(pool);
}

void test_tensor()
{
    // Describe Scalars
    test_tensor_000();
    test_tensor_001();
    test_tensor_002();
    test_tensor_003();
    test_tensor_004();
    test_tensor_005();

    // Describe Vectors
    test_tensor_010();

    // Print Vectors
    test_tensor_020();
    test_tensor_021();
    test_tensor_022();
    test_tensor_023();
    test_tensor_024();
    test_tensor_025();

    // Print Scalars
    test_tensor_030();
    test_tensor_031();
    test_tensor_032();
    test_tensor_033();
    test_tensor_034();
    test_tensor_035();
}

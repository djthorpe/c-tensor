#include <stdio.h>

#include <tensor/base.h>
#include <tensor/tensor.h>
#include <tensor/string.h>
#include "test.h"

#define buf_size 80
static char buf[buf_size];

void test_tensor_000()
{
    printf("Running test_tensor_000 (create 2x2 tensor of float32)\n");
    tensor_pool_t *pool = tensor_pool_create(2 * 1024);
    ASSERT_NOTNULL(pool);

    tensor_t *tensor = tensor_create_float32(pool, (uint32_t[]){2, 2, 0}, (float[]){1.0, 2.0, 3.0, 4.0});
    ASSERT_NOTNULL(tensor);

    printf("  2x2 tensor: %s\n", tensor_cstring(buf, buf_size, tensor_str_print(pool, tensor)));
    ASSERT(!tensor_is_scalar(tensor));
    ASSERT(!tensor_is_vector(tensor));
    ASSERT(tensor_ndims(tensor) == 2);
    ASSERT(tensor_nelems(tensor) == 4);


    tensor_t *zero = tensor_create_float32(pool, (uint32_t[]){2, 2, 2, 0}, NULL);
    ASSERT_NOTNULL(zero);

    printf("  2x2x2 tensor: %s\n", tensor_cstring(buf, buf_size, tensor_str_print(pool, zero)));
    ASSERT(!tensor_is_scalar(zero));
    ASSERT(!tensor_is_vector(zero));
    ASSERT(tensor_ndims(zero) == 3);
    ASSERT(tensor_nelems(zero) == 8);

    tensor_pool_destroy(pool);
}

void test_tensor()
{
    test_tensor_000();
}

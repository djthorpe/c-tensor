#include <tensor/tensor.h>
#include <stdio.h>
#include <assert.h>

int main()
{
    tensor_pool_t *pool = tensor_pool_create(1024);
    assert(pool != NULL);

    tensor_t *a = tensor_int32(pool, 1);
    assert(a);

    tensor_t *b = tensor_int32_vec(pool, (int32_t[]){1, 2, 3}, 3);
    assert(b);

    printf("a=%s\n", tensor_cstring(tensor_describe(pool, a)));
    printf("b=%s\n", tensor_cstring(tensor_describe(pool, b)));

    tensor_pool_destroy(pool);
    return 0;
}

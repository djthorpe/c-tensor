#include <tensor/tensor.h>
#include <stdio.h>
#include <assert.h>

int main() {
    tensor_pool_t *pool = tensor_pool_create(1024);
    assert(pool != NULL);

    tensor_t* t = tensor_create_int32(pool, (uint32_t[]){1,1,1,1,0});
    assert(t);

    printf("%s\n", tensor_cstring(tensor_describe(pool, t)));

    tensor_pool_destroy(pool);
    return 0;
}

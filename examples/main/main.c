#include <tensor/tensor.h>
#include <stdio.h>
#include <assert.h>

int main()
{
    tensor_pool_t *pool = tensor_pool_create(1024);
    assert(pool);

    tensor_t *a = tensor_int32(pool, 2);
    assert(a);

    tensor_t *b = tensor_float32_vec(pool, (float[]){1, 2, 3}, 3);
    assert(b);

    // We cast a value to a float32
    tensor_t *c = tensor_cast(pool,FLOAT32_T, a);
    assert(c);

    // And then we multiply b by the scalar value c
    tensor_t *d = tensor_mul(pool, b, c);
    assert(d);

    printf("computing graph....\n");

    // Now we need to create a graph with d as the output, in order
    // to evaluate it
    tensor_graph_t *graph = tensor_graph_create(pool, d);

    // Returns the output tensor, which is d
    tensor_t *output = tensor_graph_evaluate(graph);
    printf("output=%s %s\n",
           tensor_cstring(tensor_str_describe(pool, output)),
           tensor_cstring(tensor_str_print(pool, output)));

    printf("Memory used=%lu bytes of %lu\n", tensor_pool_used(pool), tensor_pool_size(pool));

    tensor_pool_destroy(pool);
    return 0;
}

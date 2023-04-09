#include <tensor/tensor.h>
#include <stdio.h>
#include <assert.h>

int main()
{
    tensor_pool_t *pool = tensor_pool_create(1024);
    assert(pool != NULL);

    tensor_t *a = tensor_int32(pool, 2);
    assert(a);

    tensor_t *b = tensor_float32_vec(pool, (float[]){1, 2, 3}, 3);
    assert(b);

    printf("a=%s\n", tensor_cstring(tensor_describe(pool, a)));
    printf("b=%s\n", tensor_cstring(tensor_describe(pool, b)));

    // We cast a value to a float32
    tensor_t *c = tensor_cast_float32(pool, a);
    assert(c);

    // And then we multiply b by the scalar value c
    tensor_t *d = tensor_mul(pool, b, c);
    assert(d);

    // Now we need to create a graph with d as the output, in order
    // to evaluate it
    tensor_graph_t *graph = tensor_graph_create(pool, d);
    
    // Returns the output tensor, which is d
    tensor_t* output = tensor_evaluate(graph);
    printf("output=%s\n", tensor_cstring(tensor_describe(pool, output)));

    tensor_pool_destroy(pool);
    return 0;
}

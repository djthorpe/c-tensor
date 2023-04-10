
#include <tensor/tensor.h>
#include <assert.h>

// Inputs for the XOR function
float tests_in[][2] = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1},
};

// Outputs for the XOR function
float tests_out[][1] = {
    {1},
    {0},
    {0},
    {1},
};

int main()
{
    tensor_pool_t *pool = tensor_pool_create(1024);
    assert(pool != NULL);

    // Create the input tensor of two elements
    tensor_t *in = tensor_create(pool, FLOAT32_T,(int32_t[]){ 2, 0 });
    assert(in);

    // Create the hidden layer with two units
    tensor_t *hidden = tensor_sum(pool, FLOAT32_T,(int32_t[]){ 2, 2 });

    tensor_pool_destroy(pool);
    return 0;
}

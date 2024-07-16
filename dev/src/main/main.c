#include <tensor/tensor.h>
#include <stdio.h>

int main()
{
    // Create a random number generator
    rand_t *seed = rand_alloc(0);
    ASSERT(seed);

    // Create a 12 element vecotr
    mat_f32_t *a = mat_f32_alloc((int[]){12, 0});
    ASSERT(a);

    // Set all elements to 99.0
    mat_f32_randn(seed, a);

    // Print it
    mat_f32_write(stdout, a);

    // Reshape it
    mat_f32_reshape(a, (int[]){3, 4, 0});

    // Print it
    mat_f32_write(stdout, a);

    // Range from 0..11
    mat_f32_arange(a);

    // Print it
    mat_f32_write(stdout, a);

    // Free
    mat_f32_free(a);
    rand_free(seed);

    // Return success
    return 0;
}

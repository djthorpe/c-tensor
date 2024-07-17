#include <tensor/tensor.h>
#include <stdio.h>

void f32_011()
{
    // Create two new values
    uint32_t shape[4] = {2, 3, 4, 5};
    mat_f32_t *a = mat_f32_alloc(shape);
    mat_f32_t *b = mat_f32_alloc(shape);
    mat_f32_set(a, b);

    ASSERT(a);
    ASSERT(b);
    ASSERT(mat_f32_equal_shape(a, b));
    ASSERT(mat_f32_equal(a, b));

    mat_f32_free(a);
    mat_f32_free(b);
}

void f32_012()
{
    // Create two new values, fill with randoms
    uint32_t shape[4] = {2, 3, 4, 5};
    mat_f32_t *a = mat_f32_alloc(shape);
    mat_f32_t *b = mat_f32_alloc(shape);
    mat_f32_set_rand(a);
    mat_f32_set_rand(b);

    ASSERT(a);
    ASSERT(b);
    ASSERT(mat_f32_equal_shape(a, b));
    ASSERT(!mat_f32_equal(a, b));

    mat_f32_free(a);
    mat_f32_free(b);
}

void f32_013()
{
    // Create two new values, fill with randoms
    uint32_t shape[4] = {2, 3, 4, 5};
    mat_f32_t *a = mat_f32_alloc(shape);
    mat_f32_t *b = mat_f32_alloc(shape);
    mat_f32_set_rand(a);
    mat_f32_set(a, b);

    ASSERT(a);
    ASSERT(b);
    ASSERT(mat_f32_equal_shape(a, b));
    ASSERT(!mat_f32_equal(a, b));

    mat_f32_free(a);
    mat_f32_free(b);
}

void main()
{
    f32_011();
}

#include <tensor/tensor.h>
#include <stdio.h>

void base_001()
{
    // Create a new matrix
    uint32_t shape[4] = {2, 3, 4, 5};
    mat_f32_t *v = mat_f32_alloc(shape);

    ASSERT(v);
    ASSERT(mat_f32_dims(v) == 4);
    ASSERT(mat_f32_elements(v) == 2 * 3 * 4 * 5);
    ASSERT(mat_f32_is_scalar(v) == false);
    ASSERT(mat_f32_is_vector(v) == false);
    ASSERT(mat_f32_is_2d(v) == false);
    ASSERT(mat_f32_is_square(v) == false);
    mat_f32_write(stdout, v);
    mat_f32_free(v);
}

void base_002()
{
    // Create a new scalar
    uint32_t shape[4] = {0};
    mat_f32_t *v = mat_f32_alloc(shape);

    ASSERT(v);
    ASSERT(mat_f32_dims(v) == 0);
    ASSERT(mat_f32_elements(v) == 1);
    ASSERT(mat_f32_is_scalar(v) == true);
    ASSERT(mat_f32_is_vector(v) == false);
    ASSERT(mat_f32_is_2d(v) == false);
    ASSERT(mat_f32_is_square(v) == false);
    mat_f32_write(stdout, v);
    mat_f32_free(v);
}

void base_003()
{
    // Create a new vector
    uint32_t shape[4] = {4, 0};
    mat_f32_t *v = mat_f32_alloc(shape);

    ASSERT(v);
    ASSERT(mat_f32_dims(v) == 1);
    ASSERT(mat_f32_elements(v) == 4);
    ASSERT(mat_f32_is_scalar(v) == false);
    ASSERT(mat_f32_is_vector(v) == true);
    ASSERT(mat_f32_is_2d(v) == false);
    ASSERT(mat_f32_is_square(v) == false);
    mat_f32_write(stdout, v);
    mat_f32_free(v);
}

void base_004()
{
    // Create a new square matrix
    uint32_t shape[4] = {6, 6, 0};
    mat_f32_t *v = mat_f32_alloc(shape);

    ASSERT(v);
    ASSERT(mat_f32_dims(v) == 2);
    ASSERT(mat_f32_elements(v) == 6 * 6);
    ASSERT(mat_f32_is_scalar(v) == false);
    ASSERT(mat_f32_is_vector(v) == false);
    ASSERT(mat_f32_is_2d(v) == true);
    ASSERT(mat_f32_is_square(v) == true);
    mat_f32_write(stdout, v);
    mat_f32_free(v);
}

void base_005()
{
    // Create a new scalar
    uint32_t shape[4] = {1, 1, 1, 1};
    mat_f32_t *v = mat_f32_alloc(shape);

    ASSERT(v);
    ASSERT(mat_f32_dims(v) == 0);
    ASSERT(mat_f32_elements(v) == 1);
    ASSERT(mat_f32_is_scalar(v) == true);
    ASSERT(mat_f32_is_vector(v) == false);
    ASSERT(mat_f32_is_2d(v) == false);
    ASSERT(mat_f32_is_square(v) == false);
    mat_f32_write(stdout, v);
    mat_f32_free(v);
}

void base_006()
{
    // Create a new vector
    uint32_t shape[4] = {1, 5, 1, 1};
    mat_f32_t *v = mat_f32_alloc(shape);

    ASSERT(v);
    ASSERT(mat_f32_dims(v) == 1);
    ASSERT(mat_f32_elements(v) == 5);
    ASSERT(mat_f32_is_scalar(v) == false);
    ASSERT(mat_f32_is_vector(v) == true);
    ASSERT(mat_f32_is_2d(v) == false);
    ASSERT(mat_f32_is_square(v) == false);
    mat_f32_write(stdout, v);
    mat_f32_free(v);
}

int main()
{
    base_001();
    base_002();
    base_003();
    base_004();
    base_005();
    base_006();

    return 0;
}

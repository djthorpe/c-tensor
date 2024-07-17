#include <tensor/tensor.h>

// Private functions
#include "private.h"

// Compute value offset for a given set of indexes
size_t mat_f32_offset(const uint32_t *s, int d, const int *indexes)
{
    size_t offset = 0;
    size_t stride = 1;

    for (int i = d - 1; i >= 0; --i)
    {
        offset += indexes[i] * stride;
        stride *= s[i];
    }

    return offset;
}

// Recursive function to print the matrix at a specific depth
void mat_f32_write_r(FILE *f, const mat_f32_t *mat, int dim, int current_dims[], int depth)
{
    if (depth == mat->d)
    {
        size_t offset = mat_f32_offset(mat->s, mat->d, current_dims);
        fprintf(f, "%f ", mat->v[offset]);
        return;
    }

    fprintf(f, "[");
    for (int i = 0; i < mat->s[depth]; ++i)
    {
        current_dims[depth] = i;
        mat_f32_write_r(f, mat, dim, current_dims, depth + 1);
        if (i < mat->s[depth] - 1)
        {
            fprintf(f, "\n");
            for (int j = 0; j <= depth; ++j)
            {
                fprintf(f, " ");
            }
        }
    }
    fprintf(f, "]");
}

// Write matrix to file handle
void mat_f32_write(FILE *f, const mat_f32_t *mat)
{
    int current_dims[MAX_DIMS] = {0};
    mat_f32_write_r(f, mat, mat->d, current_dims, 0);
    printf("\n");
}
#ifndef MAT_F32_PRIVATE_H
#define MAT_F32_PRIVATE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Define the maximum number of dimensions
#define MAX_DIMS 4

// Define a value structure, which includes the allocated data
// values, the number of elements, the number of dimensions, and
// the shape of the matrix. Maximum number of dimensions is 4
// and maximum number of elements in any dimension is UINT32_MAX
struct mat_f32_struct
{
    // Data
    float *v;
    // Size
    size_t n;
    // Dimensions
    int d;
    // Shape
    uint32_t s[MAX_DIMS];
};

#endif

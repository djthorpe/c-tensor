#ifndef MAT_F32_PRIVATE_H
#define MAT_F32_PRIVATE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Define the maximum number of dimensions
#define MAX_DIMS 4

// Define a matrix structure
struct mat_f32_struct
{
    // Values
    float *v;
    // Size
    size_t n;
    // Dimensions
    int d;
    // Shape
    int s[MAX_DIMS];
};

#endif

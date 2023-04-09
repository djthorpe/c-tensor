
#ifndef TENSOR_TENSOR_H
#define TENSOR_TENSOR_H

struct tensor_instance
{
    // Data type
    tensor_dtype_t dtype;

    // Number of dimensions and values
    uint8_t ndims;
    uint32_t nvalues;

    // Number of elements in each dimension
    uint32_t dims[TENSOR_MAX_DIMS];

    // Data
    void *data;
};

#endif // TENSOR_TENSOR_H

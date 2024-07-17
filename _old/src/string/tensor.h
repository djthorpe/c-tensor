#ifndef TENSOR_PRIVATE_STRING_TENSOR_H
#define TENSOR_PRIVATE_STRING_TENSOR_H

#include "tensor_private.h"

// Return const char* represtenation of a dtype or NULL
const char *tensor_dtype_str(tensor_dtype_t dtype);

// Return const char* represtenation of a tensor operation or NULL
const char *tensor_op_str(tensor_op_t op);

#endif

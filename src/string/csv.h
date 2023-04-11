#ifndef TENSOR_PRIVATE_CSV_H
#define TENSOR_PRIVATE_CSV_H

#include "tensor_private.h"

struct tensor_str_csv_instance
{
    // The memory pool
    tensor_pool_t* pool;
    
    // The field separator
    char sep;

    // The token delimiters
    char* delimiters;
};

#endif

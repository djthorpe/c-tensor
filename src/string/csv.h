#ifndef TENSOR_PRIVATE_CSV_H
#define TENSOR_PRIVATE_CSV_H

#include "tensor_private.h"

struct tensor_csv_instance
{
    // The field separator
    char sep;

    // The quote character
    char quote;
};

#endif

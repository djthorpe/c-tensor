#ifndef TENSOR_PRIVATE_CSV_H
#define TENSOR_PRIVATE_CSV_H

#include "tensor_private.h"

struct tensor_str_csv_instance
{
    // The field separator
    char sep;

    // The token delimiters
    char *delimiters;

    // In quote
    bool in_quote;

    // At start of line or delimiter
    bool in_text;

    // The current row being parsed
    tensor_str_token_t *row;
};

#endif

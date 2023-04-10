
#include <assert.h>
#include <stdio.h>

#include <tensor/tensor.h>
#include <tensor/csv.h>

struct tensor_csv_token_instance
{
    uint32_t index;
    struct tensor_csv_token_instance *next;
};

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

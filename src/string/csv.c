#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Create a CSV parser, with the given separator (usually ',', ';' or '\t')
tensor_str_csv_t *tensor_str_csv_create(tensor_pool_t *pool, const char sep)
{
    assert(pool != NULL);

    tensor_str_csv_t *csv = tensor_pool_alloc(pool, sizeof(tensor_str_csv_t), NULL);
    if (csv == NULL)
    {
        return NULL;
    }

    // Initialize the CSV parser
    csv->pool = pool;
    csv->sep = sep ? sep : ',';

    // Allocate the delimiters we are going to use
    // to split the tokens
    csv->delimiters = tensor_pool_alloc(pool, 5, NULL);
    if (csv->delimiters == NULL)
    {
        return NULL;
    }
    csv->delimiters[0] = '#';
    csv->delimiters[1] = '"';
    csv->delimiters[2] = '\n';
    csv->delimiters[3] = csv->sep;
    csv->delimiters[4] = 0;

    // Return success
    return csv;
}

// Consume a string of CSV data and return the fields as a list of tokens.
// Returns NULL on error.
tensor_str_token_t *tensor_str_csv_parseline(tensor_str_csv_t *csv, tensor_str_t *str, void *user_data)
{
    assert(csv != NULL);
    assert(str != NULL);

    // Tokenize the string
    tensor_str_token_t *head = tensor_str_tokenize(csv->pool, str, csv->delimiters, true, user_data);
    if (head == NULL)
    {
        return NULL;
    }

    tensor_str_token_t *token = head;
    while (token)
    {
        // TODO
        token = tensor_str_token_next(token);
    }

    return head;
}

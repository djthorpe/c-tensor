
#ifndef TENSOR_CSV_H
#define TENSOR_CSV_H

#include <tensor/tensor.h>

///////////////////////////////////////////////////////////////////////////////

// Opaque csv_tokens type
typedef struct tensor_csv_instance tensor_csv_t;

// Opaque list of tokens
typedef struct tensor_csv_token_instance tensor_csv_token_t;

///////////////////////////////////////////////////////////////////////////////

// Create a CSV parser
tensor_csv_t *tensor_csv_create(tensor_pool_t *pool,const char sep);

// Consume a line of CSV data. Returns false on error
bool tensor_csv_parseline(tensor_csv_t * csv, const char *line);

// Get the number of lines read
uint32_t tensor_csv_nlines(tensor_csv_t *csv);

// Check for end of row
bool tensor_csv_eor(tensor_csv_t *csv);

#endif



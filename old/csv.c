
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <tensor/tensor.h>
#include <tensor/csv.h>

struct tensor_csv_instance
{
    // The field separator
    char sep;

    // The quote character
    char quote;

    // The number of lines read
    uint32_t nlines;

    // Is in a double quoted string
    bool inquote;

    // The linked list of tokens
    tensor_csv_token_t *tokens;
};

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

void tensor_csv_sep(tensor_csv_t *csv, const char *line, int d)
{
    printf("sep %d ",d);
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Create a CSV parser
tensor_csv_t *tensor_csv_create(tensor_pool_t *pool, const char sep)
{
    assert(pool != NULL);

    tensor_csv_t *csv = tensor_pool_alloc(pool, sizeof(tensor_csv_t), NULL);
    if (csv == NULL)
    {
        return NULL;
    }
    csv->sep = sep;
    csv->quote = '"';
    csv->nlines = 0;
    csv->inquote = false;
    csv->tokens = NULL;

    return csv;
}

// Consume a line of CSV data. Returns false on error
bool tensor_csv_parseline(tensor_csv_t *csv, const char *line)
{
    assert(csv != NULL);
    assert(line != NULL);

    // Increment the number of lines seen
    csv->nlines++;

    // Cycle through
    int i = 0;
    for (const char *ptr = line; *ptr; ptr++, i++)
    {
        // If we are in a quote, look for the end quote
        if (csv->inquote)
        {
            // Check for quote, and peek at the next character to see if it's also a quote
            if (*ptr == csv->quote && *(ptr + 1) == csv->quote)
            {
                ptr++;
                continue;
            }
            if (*ptr == csv->quote)
            {
                csv->inquote = false;
            }
            continue;
        }

        // Check for separator
        char ch = *ptr;
        if (ch == csv->sep)
        {
            // TODO
            tensor_csv_sep(csv, line, i);
        }
        else if (ch == csv->quote)
        {
            csv->inquote = true;
        }
    }
    return true;
}

// Get the number of lines read
inline uint32_t tensor_csv_nlines(tensor_csv_t *csv)
{
    assert(csv != NULL);
    return csv->nlines;
}

// Check for end of row
bool tensor_csv_eor(tensor_csv_t *csv)
{
    assert(csv != NULL);
    return !csv->inquote;
}

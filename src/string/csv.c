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
tensor_str_token_t *tensor_str_csv_parse(tensor_str_csv_t *csv, tensor_str_t *str, void *user_data)
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
        // Return non-delimiter tokens as text
        if (token->token_type == DELIMITER_T)
        {
            if (tensor_str_token_is_delimiter(token, '"'))
            {
                // If not in a quote, then change to TEXT_T
                if (csv->in_quote)
                {
                    // Peak forward to the next quote
                    if (token->next != NULL && tensor_str_token_is_delimiter(token->next, '"'))
                    {
                        // Set current token to TEXT_T and when we move to the next token,
                        // it will be ignored
                        token->token_type = TEXT_T;
                    }
                    else
                    {
                        // Otherwise, we are out of the quote
                        csv->in_quote = false;
                        token->token_type = IGNORE_T;
                    }
                }
                else
                {
                    csv->in_quote = true;
                    token->token_type = IGNORE_T;
                }
            }
            else if (tensor_str_token_is_delimiter(token, '\n'))
            {
                if (csv->in_quote)
                {
                    token->token_type = TEXT_T;
                }
                else
                {
                    // TODO: if the last token was also EOL_T then ignore this one
                    token->token_type = END_T;
                    token->str = NULL;
                }
            }
            else if (!tensor_str_token_is_delimiter(token, csv->sep))
            {
                // TODO: Ignore whitespace after a delimiter
                token->token_type = TEXT_T;
            }
        }

        // Move to next token
        token = tensor_str_token_next(token);
    }

    return head;
}

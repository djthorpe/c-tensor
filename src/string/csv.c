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
    assert(pool);

    tensor_str_csv_t *csv = tensor_pool_alloc(pool, sizeof(tensor_str_csv_t), NULL);
    if (csv == NULL)
    {
        return NULL;
    }

    // Initialize the CSV parser
    csv->sep = sep ? sep : ',';
    csv->row = NULL;
    csv->in_quote = false;
    csv->in_text = false;

    // Allocate the delimiters we are going to use
    // to split the tokens
    csv->delimiters = tensor_pool_alloc(pool, 10, NULL);
    if (csv->delimiters == NULL)
    {
        return NULL;
    }
    csv->delimiters[0] = '#';
    csv->delimiters[1] = '"';
    csv->delimiters[2] = '\n';
    csv->delimiters[3] = '\r';
    csv->delimiters[4] = csv->sep;
    csv->delimiters[5] = 0;

    // Return success
    return csv;
}

/*
 * Consume a string of CSV data and return the fields as a list of tokens
 */
tensor_str_token_t *tensor_str_csv_parse(tensor_pool_t *pool, tensor_str_csv_t *csv, tensor_str_t *str, void *user_data)
{
    assert(pool);
    assert(csv);
    assert(str);

    // Create a new token list
    tensor_str_token_t *head = tensor_str_tokenize(pool, str, csv->delimiters, true, user_data);
    if (head == NULL)
    {
        return NULL;
    }

    tensor_str_token_t *token = head;
    while (token)
    {
        // Return non-delimiter tokens as text or ignore them
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
                        csv->in_text = false;
                        token->token_type = IGNORE_T;
                    }
                }
                else
                {
                    csv->in_quote = true;
                    csv->in_text = true;
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
                    token->token_type = END_T;
                    token->str = NULL;
                    csv->in_text = false;
                }
            }
            else if (!tensor_str_token_is_delimiter(token, csv->sep))
            {
                token->token_type = TEXT_T;
            }
            else if (csv->in_quote)
            {
                token->token_type = TEXT_T;
            }
        }
        else if (token->token_type == SPACE_T)
        {
            if (csv->in_quote)
            {
                token->token_type = TEXT_T;
            }
        }

        // Move to next token
        token = tensor_str_token_next(token);
    }
    return head;
}

// TODO
#define buf_size 80
static char buf[buf_size];

/*
 * Print output fields
 */
bool tensor_str_csv_output(tensor_pool_t *pool, tensor_str_csv_t *csv, tensor_str_token_t *tokens)
{
    assert(pool);
    assert(csv);
    assert(tokens);

    // Create an empty string to accumulate the output
    tensor_str_t *str = tensor_str_create(pool, 0);
    if (str == NULL)
    {
        return false;
    }

    // Iterate through the tokens
    while (tokens)
    {
        // Ignore START_T tokens
        if (tokens->token_type == START_T)
        {
            // Do nothing
        }
        else if (tokens->token_type == TEXT_T || tokens->token_type == SPACE_T)
        {
            if (!tensor_str_concat(str, tokens->str))
            {
                return false;
            }
        }
        else if (tokens->token_type == DELIMITER_T || tokens->token_type == END_T)
        {
            // Append a TEXT_T token onto the list of tokens
            csv->row = tensor_str_token_append(pool, csv->row, TEXT_T, tokens->user_data);
            csv->row->str = tensor_str_dup(pool, str);
            tensor_str_zero(str);
            fputs(tensor_cstring(buf, buf_size, tensor_str_token_describe(pool, csv->row)), stdout);

            // Append the END_T token onto the list of tokens
            if (tokens->token_type == END_T)
            {
                csv->row = tensor_str_token_append(pool, csv->row, END_T, tokens->user_data);
                fputs(tensor_cstring(buf, buf_size, tensor_str_token_describe(pool, csv->row)), stdout);
                fputs("\n", stdout);
            }
            else
            {
                fputs(" ", stdout);
            }
        }
        tokens = tensor_str_token_next(tokens);
    }

    // Reset: Set csv->row to NULL
    csv->row = NULL;

    return true;
}

#include <assert.h>
#include <string.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Create a list of tokens from a string, separated by the given set of delimiters and
// optionally including the delimiters in the list of tokens. Returns NULL on
// memory allocation error or zero-valued string. If delimiters is NULL then
// use the default set of delimiters, which is the set if whitespace characters
// and NULL
tensor_str_token_t *tensor_str_tokenize(tensor_pool_t *pool, tensor_str_t *str, void *user_data, char *delimiters, bool keep_delimiters) {
    assert(pool != NULL);
    assert(str != NULL);

    // Empty string returns NULL
    if (str->size == 0) {
        return NULL;
    }
    assert(str->data);

    // Iterate through the string, looking for delimiters
    for(void* ptr = str->data; ptr < str->data + str->size; ptr++) {
        // TODO: Check if this is a delimiter
        printf("Checking %c\n", *(char*)ptr);
    }

    return NULL;
}

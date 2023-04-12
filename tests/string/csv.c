#include <stdio.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "test.h"


#define buf_size 80
static char buf[buf_size];

// Simple case with two tokens and no quotes, with no trailing newline
// rows = 1 tokens = 2
const char *test_100 = "Hello,World";

// More complex case with quotes and newlines
// rows = 5 tokens = 5
const char *test_101 = "Year,Make,Model,Description,Price\n1997,Ford,E350,\"ac, abs, moon\",3000.00\n1999,Chevy,\"Venture \"\"Extended Edition\"\"\",\"\",4900.00\n1999,Chevy,\"Venture "
                       "Extended Edition, Very Large\"\"\",\"\",5000.00\n1996,Jeep,Grand Cherokee,\"MUST SELL!\nair, moon roof, loaded\",4799.00\n";

// Simple case with blank lines
// rows = 3 tokens = 4
const char *test_102 = "Year,Make,Model,Length\n\n1997,Ford,E350,2.35\n2000,Mercury,Cougar,2.38\n\n\n";

// Case with semicolon as delimiter
// rows = 3 tokens = 4
const char *test_103 = "\n\nYear;Make;Model;Length\n1997;Ford;E350;2,35\n2000;Mercury;Cougar;2,38\n";

void test_csv_100()
{
    printf("Running test_csv_100\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    // Test the simple case
    tensor_str_csv_t *csv = tensor_str_csv_create(pool, 0);
    ASSERT_NOTNULL(csv);
    tensor_str_t *str = tensor_str_create(pool, (char *)test_100);
    ASSERT_NOTNULL(str);
    tensor_str_token_t *token = tensor_str_csv_parse(csv, str, NULL);
    ASSERT_NOTNULL(token);

    printf("  csv=%s\n", test_100);
    while (token)
    {
        printf("  token=%s\n", tensor_cstring(buf, buf_size, tensor_str_token_describe(pool, token)));
        token = tensor_str_token_next(token);
    }

    tensor_pool_destroy(pool);
}

void test_csv()
{
    test_csv_100();
}

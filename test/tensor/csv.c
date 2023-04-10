#include <stdio.h>

#include <tensor/tensor.h>
#include <tensor/csv.h>
#include "test.h"

// Simple case with two tokens and no quotes, with no trailing newline
// rows = 1 tokens = 2
const char* test_100 = "Hello,World";

// More complex case with quotes and newlines
// rows = 5 tokens = 5
const char* test_101 = "Year,Make,Model,Description,Price\n1997,Ford,E350,\"ac, abs, moon\",3000.00\n1999,Chevy,\"Venture \"\"Extended Edition\"\"\",\"\",4900.00\n1999,Chevy,\"Venture ""Extended Edition, Very Large\"\"\",\"\",5000.00\n1996,Jeep,Grand Cherokee,\"MUST SELL!\nair, moon roof, loaded\",4799.00\n";

// Simple case with blank lines
// rows = 3 tokens = 4
const char* test_102 = "Year,Make,Model,Length\n\n1997,Ford,E350,2.35\n2000,Mercury,Cougar,2.38\n\n\n";

// Case with semicolon as delimiter
// rows = 3 tokens = 4
const char* test_103 = "\n\nYear;Make;Model;Length\n1997;Ford;E350;2,35\n2000;Mercury;Cougar;2,38\n";

void test_csv_000()
{
    printf("Running test_csv_000\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_csv_t *csv = tensor_csv_create(pool, ',');
    ASSERT_NOTNULL(csv);
    bool success = tensor_csv_parseline(csv, "Hello,World");
    ASSERT(success);
    ASSERT(tensor_csv_eor(csv));
    ASSERT_EQUALS(1, tensor_csv_nlines(csv));

    tensor_pool_destroy(pool);
}

void test_csv()
{
    test_csv_000();
}

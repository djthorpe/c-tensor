
#ifndef TEST_H
#define TEST_H

#include <assert.h>
#include <string.h>

#define ASSERT(x) assert(x)
#define ASSERT_NOTNULL(x) assert(x != NULL)
#define ASSERT_NULL(x) assert(x == NULL)
#define ASSERT_EQUALS(x,y) assert(x == y)
#define ASSERT_NOTEQUALS(x,y) assert(x != y)
#define ASSERT_EQUALS_STR(x,y) assert(strcmp(x,y) == 0)
#endif

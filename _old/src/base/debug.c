#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

/*
 * Print an expression and Panic
 */
void tensor_panic(const char *file, int line, const char *expr) {
    fprintf(stderr, "PANIC: %s:%d: %s\n", file, line, expr);
    abort();
}

/*
 * Print a debug message
 */
void tensor_printf(const char *file, int line, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "%s:%d: ", file, line);
    vfprintf(stderr, fmt, args);
}

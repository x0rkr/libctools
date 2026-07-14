#ifndef LIBCTOOLS_STD_H
#define LIBCTOOLS_STD_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

//println()
void println(const char *format, ...);

//strreplace()
char *strreplace(const char *str, const char *old_sub, const char *new_sub);

// --- Generic Vector Module ---
#define VECTOR_INIT_CAPACITY 4

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t elem_size;
} vector_t;

void vector_init(vector_t *v, size_t elem_size);
void vector_free(vector_t *v);
bool vector_push_back(vector_t *v, const void *element);
void *vector_get(const vector_t *v, size_t index);
bool vector_set(vector_t *v, size_t index, const void *element);

#endif /* LIBCTOOLS_STD_H */
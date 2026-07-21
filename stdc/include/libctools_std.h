#ifndef LIBCTOOLS_STD_H
#define LIBCTOOLS_STD_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

//println()
void println(const char *format, ...) __attribute__((format(printf, 1, 2)));

//strreplace()
char *strreplace(const char *str, const char *old_sub, const char *new_sub);

//Generic Vector Module 
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

//Hash table
typedef struct ht_node {
    char *key;
    void *value;
    struct ht_node *next;
} ht_node_t;


typedef struct {
    ht_node_t **buckets;
    size_t size;
    size_t count;
} hash_table_t;

// Hash Table API
hash_table_t *ht_create(size_t initial_size);
bool ht_insert(hash_table_t *ht, const char *key, void *value);
void *ht_get(hash_table_t *ht, const char *key);
bool ht_remove(hash_table_t *ht, const char *key);
void ht_destroy(hash_table_t *ht);
// Hash Table API

#endif /* LIBCTOOLS_STD_H */
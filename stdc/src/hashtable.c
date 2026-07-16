#include "libctools_std.h"
#include <stdlib.h>
#include <string.h>

// Standard DJB2 string hashing algorithm
static unsigned long djb2_hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++)) {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Allocate and initialize a generic hash table
hash_table_t *ht_create(size_t initial_size) {
    if (initial_size == 0) {
        return NULL;
    }

    hash_table_t *ht = malloc(sizeof(hash_table_t));
    if (!ht) {
        return NULL;
    }

    // Allocate array of node pointers initialized to NULL
    ht->buckets = calloc(initial_size, sizeof(ht_node_t *));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }

    ht->size = initial_size;
    ht->count = 0;

    return ht;
}
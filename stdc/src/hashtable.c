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

bool ht_insert(hash_table_t *ht, const char *key, void *value) {
    if (!ht || !key) return false;

    // Calculate the target bucket bucket index
    unsigned long hash = djb2_hash(key);
    size_t index = hash % ht->size;

    // Step 1: Scan the bucket's chain to check if the key already exists
    ht_node_t *current = ht->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value; // Update the value in-place
            return true;
        }
        current = current->next;
    }

    // Step 2: Key doesn't exist, allocate a new node
    ht_node_t *new_node = malloc(sizeof(ht_node_t));
    if (!new_node) return false;

    new_node->key = strdup(key); // Duplicate key string to own the memory
    if (!new_node->key) {
        free(new_node);
        return false;
    }
    
    new_node->value = value;

    // Step 3: Insert at the head of the singly linked list (Chaining)
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    ht->count++;

    return true;
}

// Retrieve a value by key from the hash table
void *ht_get(hash_table_t *ht, const char *key) {
    if (!ht || !key) return NULL;

    unsigned long hash = djb2_hash(key);
    size_t index = hash % ht->size;

    // Traverse the chain at the calculated index
    ht_node_t *current = ht->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value; // Match found
        }
        current = current->next;
    }

    return NULL; // Key not found
}

// Safely free all memory allocated for the hash table
void ht_destroy(hash_table_t *ht) {
    if (!ht) return;

    // Free each individual node chain
    for (size_t i = 0; i < ht->size; i++) {
        ht_node_t *current = ht->buckets[i];
        while (current != NULL) {
            ht_node_t *temp = current;
            current = current->next;
            
            free(temp->key);   // Free the duplicated key
            free(temp);        // Free the node structure
        }
    }

    free(ht->buckets); // Free the master bucket pointer array
    free(ht);          // Free the control block
}
#include "libctools_std.h"
#include <stdlib.h>
#include <string.h>

// Initialize the vector with a starting capacity
void vector_init(vector_t *v, size_t elem_size) {
    if (!v) return;
    
    v->elem_size = elem_size;
    v->size = 0;
    v->capacity = VECTOR_INIT_CAPACITY;
    
    // Allocate heap memory for the starting capacity
    v->data = malloc(v->capacity * v->elem_size);
}

// Safely free memory and zero-out the struct
void vector_free(vector_t *v) {
    if (!v) return;
    
    if (v->data) {
        free(v->data);
        v->data = NULL;
    }
    
    v->size = 0;
    v->capacity = 0;
    v->elem_size = 0;
}
// Push an element to the back, resizing the container dynamically if full
bool vector_push_back(vector_t *v, const void *element) {
    if (!v || !element) return false;

    // Check if we need to expand our dynamic array capacity
    if (v->size >= v->capacity) {
        size_t new_capacity = v->capacity * 2;
        void *new_data = realloc(v->data, new_capacity * v->elem_size);
        if (!new_data) {
            return false; // Out of memory!
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }

    // Calculate memory offset destination and copy the bytes over
    char *target = (char *)v->data + (v->size * v->elem_size);
    memcpy(target, element, v->elem_size);
    v->size++;

    return true;
}

// Get a generic pointer to the element at a specific index
void *vector_get(const vector_t *v, size_t index) {
    if (!v || index >= v->size) return NULL;

    // Compute pointer offset in bytes
    return (char *)v->data + (index * v->elem_size);
}

// Set/overwrite an element at a specific index
bool vector_set(vector_t *v, size_t index, const void *element) {
    if (!v || !element || index >= v->size) return false;

    // Compute pointer offset in bytes and copy new element
    char *target = (char *)v->data + (index * v->elem_size);
    memcpy(target, element, v->elem_size);
    
    return true;
}
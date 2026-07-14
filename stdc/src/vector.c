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
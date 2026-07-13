#include "libctools_emb.h"

// 1. Initialize the queue pointers
void ring_buffer_init(ring_buffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
}

// 2. Check if buffer contains no unread elements
bool ring_buffer_is_empty(const ring_buffer_t *rb) {
    return rb->head == rb->tail;
}

// 3. Check if buffer is completely full
bool ring_buffer_is_full(const ring_buffer_t *rb) {
    // Standard circular queue math: next head position would match tail
    return ((rb->head + 1) % RING_BUFFER_SIZE) == rb->tail;
}

// 4. Push a single byte into the buffer (Write operation)
bool ring_buffer_push(ring_buffer_t *rb, uint8_t data) {
    if (ring_buffer_is_full(rb)) {
        return false; // Buffer overflow safety check
    }
    
    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % RING_BUFFER_SIZE; // Wrap around using modulo
    return true;
}

// 5. Pop a single byte out of the buffer (Read operation)
bool ring_buffer_pop(ring_buffer_t *rb, uint8_t *data) {
    if (ring_buffer_is_empty(rb)) {
        return false; // Buffer underflow safety check
    }
    
    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE; // Wrap around using modulo
    return true;
}
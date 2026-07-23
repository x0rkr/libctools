#ifndef LIBCTOOLS_EMB_H
#define LIBCTOOLS_EMB_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Println for embedded target
void println(const char *format, ...);

// --- Ring Buffer Module ---
#define RING_BUFFER_SIZE 64

typedef struct {
    uint8_t buffer[RING_BUFFER_SIZE];
    size_t head;
    size_t tail;
} ring_buffer_t;

void ring_buffer_init(ring_buffer_t *rb);
bool ring_buffer_is_empty(const ring_buffer_t *rb);
bool ring_buffer_is_full(const ring_buffer_t *rb);
bool ring_buffer_push(ring_buffer_t *rb, uint8_t data);
bool ring_buffer_pop(ring_buffer_t *rb, uint8_t *data);

//Mempool
#define MEMPOOL_MAX_BLOCKS 32

typedef struct {
    uint8_t *buffer;          
    size_t block_size;       
    size_t num_blocks;       
    uint32_t alloc_mask;      
} memory_t;

// Memory Pool API
bool memory_init(memory_t *mp, uint8_t *buffer, size_t block_size, size_t num_blocks);
void *memory_alloc(memory_t *mp);
bool memory_free(memory_t *mp, void *block_ptr);
size_t memory_used_count(const memory_t *mp);

#endif // LIBCTOOLS_EMB_H
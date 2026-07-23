#include "libctools_emb.h"

// Initialize the memory pool structure
bool memory_init(memory_t *mp, uint8_t *buffer, size_t block_size, size_t num_blocks) {
    if (!mp || !buffer || block_size == 0 || num_blocks == 0 || num_blocks > MEMORY_MAX_BLOCKS) {
        return false;
    }

    mp->buffer = buffer;
    mp->block_size = block_size;
    mp->num_blocks = num_blocks;
    mp->alloc_mask = 0U;

    return true;
}

// Return the current number of allocated blocks
size_t memory_used_count(const memory_t *mp) {
    return mp ? (size_t)__builtin_popcount(mp->alloc_mask) : 0;
}

// Allocate a block from the pool in O(1) time
void *memory_alloc(memory_t *mp) {
    if (!mp) return NULL;

    // Invert mask to find free slots
    uint32_t free_mask = ~mp->alloc_mask;
    
    // Mask off unused blocks beyond capacity safely
    if (mp->num_blocks < MEMORY_MAX_BLOCKS) {
        free_mask &= (1U << mp->num_blocks) - 1U;
    }

    if (!free_mask) {
        return NULL; // Pool exhausted
    }

    int free_index = __builtin_ctz(free_mask);
    mp->alloc_mask |= (1U << free_index);

    return mp->buffer + (free_index * mp->block_size);
}

// Free a block back into the pool in O(1) time
bool memory_free(memory_t *mp, void *block_ptr) {
    if (!mp || !block_ptr) return false;

    uint8_t *ptr = (uint8_t *)block_ptr;
    size_t total_bytes = mp->num_blocks * mp->block_size;

    // Fast bounds check
    if (ptr < mp->buffer || ptr >= (mp->buffer + total_bytes)) {
        return false;
    }

    size_t offset = (size_t)(ptr - mp->buffer);

    // Exact block boundary alignment check
    if (offset % mp->block_size != 0) {
        return false;
    }

    size_t block_index = offset / mp->block_size;

    // Double-free guard: check if block is actually allocated
    if (!(mp->alloc_mask & (1U << block_index))) {
        return false;
    }

    // Clear bit
    mp->alloc_mask &= ~(1U << block_index);

    return true;
}
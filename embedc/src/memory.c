#include "libctools_emb.h"

// Initialize the memory pool structure
bool mempool_init(mempool_t *mp, uint8_t *buffer, size_t block_size, size_t num_blocks) {
    if (!mp || !buffer || block_size == 0 || num_blocks == 0) {
        return false;
    }
    
    // Safety check: Our 32-bit mask can only track up to 32 blocks
    if (num_blocks > MEMPOOL_MAX_BLOCKS) {
        return false;
    }

    mp->buffer = buffer;
    mp->block_size = block_size;
    mp->num_blocks = num_blocks;
    mp->alloc_mask = 0; // All blocks start as free (0)

    return true;
}

// Return the current number of allocated blocks
size_t mempool_used_count(const mempool_t *mp) {
    if (!mp) {
        return 0;
    }
    
    // GCC compiler intrinsic to count set bits in O(1) cycles
    return (size_t)__builtin_popcount(mp->alloc_mask);
}

// Allocate a block from the pool in O(1) time
void *mempool_alloc(mempool_t *mp) {
    if (!mp) return NULL;

    // Check if the pool is completely full
    uint32_t free_mask = ~mp->alloc_mask;
    
    // Mask off bits beyond our block count limit
    if (mp->num_blocks < MEMPOOL_MAX_BLOCKS) {
        free_mask &= (1U << mp->num_blocks) - 1;
    }

    if (free_mask == 0) {
        return NULL; // Out of blocks!
    }

    // Find the first free block index (count trailing zeros of free_mask)
    int free_index = __builtin_ctz(free_mask);

    // Mark it as allocated (set bit to 1)
    mp->alloc_mask |= (1U << free_index);

    // Calculate pointer to the allocated block segment
    return mp->buffer + (free_index * mp->block_size);
}

// Free a block back into the pool in O(1) time
bool mempool_free(mempool_t *mp, void *block_ptr) {
    if (!mp || !block_ptr) return false;

    uint8_t *ptr = (uint8_t *)block_ptr;

    // Bounds check: Make sure the pointer actually points inside our buffer
    if (ptr < mp->buffer || ptr >= (mp->buffer + (mp->num_blocks * mp->block_size))) {
        return false;
    }

    // Alignment check: Ensure pointer points to the exact start of a block boundary
    size_t offset = ptr - mp->buffer;
    if (offset % mp->block_size != 0) {
        return false;
    }

    size_t block_index = offset / mp->block_size;

    // Clear the bit (set to 0) to mark it as free
    mp->alloc_mask &= ~(1U << block_index);

    return true;
}
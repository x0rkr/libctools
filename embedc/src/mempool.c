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
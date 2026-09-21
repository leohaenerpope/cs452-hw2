#ifndef BALLOC_H
#define BALLOC_H

#include "utils.h"

typedef void *Balloc;

/**
 * Creates and returns a Balloc (which points to a BallocData struct pointer,
 * which holds:
 * size_t size;
    int l; -- MUST BE AT LEAST 3 - due to 64 bit memory only letting min
    int u; -- ALSO MUST BE AT LEAST 3
    void *mem;
    FreeList fl;
    BBM *map; - buddy bit maps (one for each freelist size value e)
    )
 * 
 * Makes sure that the passed U value is handled correctly (even when not a 2^e value)
 * Blocks are allocated adequately (multiple 2^u if we have to), then smaller and smaller (inside of freelist)
 * 
 * Utilizes the mmalloc function to allocate memory. 
 */
extern Balloc bcreate(unsigned int size, int l, int u);
/**
 * Frees a BallocData (pointer pointed to by POOL) from memory,
 * including it's own memory, and free list and buddy bit maps.
 */
extern void   bdelete(Balloc pool);

/**
 * Allocates an amount of memory inside of the Balloc
 * 
 * NOTE: The lowest amount of size is 8 bytes - pointers have to be 8 bytes (64-bit system) and will spill over if we are allocating <8 byte amounts
 * 
 * Uses freelistalloc() to utilize the free list to allocate the memory
 * Then updates the bitmap for whatever buddy block is now in use for the memory
 * 
 * Returns the memory point
 */
extern void *balloc(Balloc pool, unsigned int size);
/**
 * Frees up memory inside of the Balloc
 * 
 * Utilizes bsize() to get the size of the memory block,
 * updates the bitmaps and also utilizes freelistfree() to put available space back onto the freelist
 */
extern void  bfree(Balloc pool, void *mem);

/**
 * Goes through the buddy bitmaps to find if the bbm
 * has a correlating bit that has it's buddy bit set to 1
 * 
 * Note that this will fail if the bit is set to 0 if both buddies are currently in use in memory.
 */
extern unsigned int bsize(Balloc pool, void *mem);
extern void bprint(Balloc pool);

#endif

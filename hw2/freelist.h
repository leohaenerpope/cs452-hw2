#ifndef FREELIST_H
#define FREELIST_H

#include <stdlib.h>

typedef void *FreeList;

/**
 * Utilizes mmalloc() to create an array of free list head pointers
 * 
 * (U-L) is the indexing for the array
 * 
 * All head pointers are initialized to NULL
 */
extern FreeList freelistcreate(size_t size, int l, int u);
/**
 * Utilizes mmfree() to free the freelist array of head pointers
 */
extern void     freelistdelete(FreeList f, int l, int u);

/**
 * Allocates and returns space (defined by E)
 * 
 * Utilizes the freelist to determine if free space is available for given e
 * 
 * If freelist doesn't have space for current e, searches upward, while breaking down
 * a larger available space into pairs, going back down to size e.
 * 
 * Returns NULL if space is not available.
 */
extern void *freelistalloc(FreeList f, void *base, int e, int l, int u);
/**
 * Puts a block of memory back on to the free list in an appropriate spot.
 * 
 * Will search for buddies at the correct size for the block to pair up with.
 * Searching for buddies utilizes the baddrinv() function from bbm, to get
 * the memory location of the buddy, and match it in the free list.
 * 
 * If we can, keep merging free space buddies together so then we can have an even
 * bigger (exponent) block of space.
 */
extern void  freelistfree(FreeList f, void *base, void *mem, int e, int l, int u);

/**
 * Utilizes the freelist to try to find the size of an allocated block.
 * 
 * Uses baddrinv() from bbm to find the buddy address of the given block,
 * then searches the freelist to find the buddy, to which the size of the buddy
 * in the freelist will be known.
 * 
 * Returns U if no buddy found (either buddy not in freelist or block is size u).
 */
extern int freelistsize(FreeList f, void *base, void *mem, int l, int u);
/**
 * Prints out the free list, starting at bottom (l) going to the top (u)
 * 
 * Prints out information about the size, then the pointers associated (for each block)
 */
extern void freelistprint(FreeList f, int l, int u);

#endif

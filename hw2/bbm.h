// A baddr bitmap, for the Buddy System.

#ifndef BBM_H
#define BBM_H

#include <stdio.h>

typedef void *BBM;

/**
 * Initializes and returns a new buddy bit map,
 * utilizing mapsize() to note how much space is needed to store information
 * about each buddy pair
 */
extern BBM  bbmcreate(size_t size, int e);
/**
 * Frees the buddy bit map from memory
 */
extern void bbmdelete(BBM b);

/**
 * Sets bit in pair bit map to 1 for a specified buddy,
 * Utilizing the base memory point, memory point of buddy we want to change, and size exponent
 */
extern void bbmset(BBM b, void *base, void *mem, int e);
/**
 * Sets bit in pair bit map to 0 for a specified buddy,
 * Utilizing the base memory point, memory point of buddy we want to change, and size exponent
 */
extern void bbmclr(BBM b, void *base, void *mem, int e);
/**
 * Tests bit in pair bit map, returning 0 or 1 for the value of specified buddy (for the pair bit map),
 * Utilizing the base memory point, memory point of buddy we want to change, and size exponent
 */
extern  int bbmtst(BBM b, void *base, void *mem, int e);

/**
 * Prints the specified bitmap utilizing bmprt function from bm
 */
extern void bbmprt(BBM b);

/**
 * Returns void buddy address spot in memory with e bit set to 1,
 * given a base memory point and current memory spot of the buddy
 */
extern void *baddrset(void *base, void *mem, int e);
/**
 * Returns void buddy address spot in memory with e bit set to 0,
 * given a base memory point and current memory spot of the buddy
 */
extern void *baddrclr(void *base, void *mem, int e);
/**
 * Returns void buddy address spot in memory with the flipped e bit to whatever was input as the memory point
 * given a base memory point and current memory spot of the buddy
 */
extern void *baddrinv(void *base, void *mem, int e);
/**
 * Tests whether bit e is set in buddy memory location
 * given a base memory point and current memory spot of the buddy
 * 
 * Returns void address spot (0 if not set, returns a number > 0 if it is)
 */
extern int   baddrtst(void *base, void *mem, int e);

#endif

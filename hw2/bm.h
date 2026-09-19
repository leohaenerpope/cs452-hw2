// A general-purpose bitmap.

#ifndef BM_H
#define BM_H

#include <stdio.h>

typedef void *BM;

/**
 * Creates a bit map in memory from a specified number of bits.
 * Using mmalloc, allocates space for size_t bit amount value and actual bit space from the specified amount.
 * Returns the pointer to the bit map that starts zeroed out, or 0 null if mmalloc fails.
 */
extern BM   bmcreate(size_t bits);


/**
 * Frees the bitmap from memory by first moving back to the start of BM memory data (the bit amount of the bitmap)
 * Then frees from memory using mmfree with:
 * size of size_t (for storing amount of bits in bitmap) + amount of space that the actual map takes up
 */
extern void bmdelete(BM b);

/**
 * Making sure that I is a proper location in B,
 * Sets specified bit I in a bitmap B to 1 using bitset
 */
extern void bmset(BM b, size_t i);
/**
 * Making sure that I is a proper location in B,
 * Sets specified bit I in a bitmap B to 0 using bitclr
 */
extern void bmclr(BM b, size_t i);
/**
 * Making sure that I is a proper location in B,
 * Returns the specified bit I value in a bitmap B i
 */
extern int  bmtst(BM b, size_t i);

/**
 * Prints out the bit map in byte hex format, starting at the last byte stored in memory,
 * then ending with the first byte
 */
extern void bmprt(BM b);

#endif

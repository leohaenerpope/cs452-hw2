// Utility functions and values used across this assignment

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

static const int bitsperbyte=8;

/**
 * Use OS (mmap) to allocate a place in memory of byte amount SIZE,
 * returning pointer to memory location
 * 
 * mmap(0, size, - 0 means OS can just choose wherever the memory goes
        PROT_READ | PROT_WRITE, - can read and write
        MAP_PRIVATE | MAP_ANONYMOUS, - private anonymous memory
        -1, 0); - no files involved
    
    mmap utilizes c library sys/mman.h
 */
extern void *mmalloc(size_t size);
/**
 * Use OS to deallocate a place in memory given the pointer P,
 * and SIZE to deallocate.
 */
extern void mmfree(void *p, size_t size);

/**
 * Performs n/d, rounding up if necessary
 */
extern size_t divup(size_t n, size_t d);
/**
 * Converts bits amount to byte amount, rounding up if necessary
 */
extern size_t bits2bytes(size_t bits);

/**
 * Returns 2^e value for a size of block
 */
extern size_t e2size(int e);
/**
 * Returns the e (exponent) value that would be 2^e = size (rounded down)
 */
extern int size2e(size_t size);

/**
 * Sets specified bit in memory using pointer P and specified bit B to 1
 */
extern void bitset(void *p, int bit);
/**
 * Sets specified bit in memory using pointer P and specified bit B to 0
 */
extern void bitclr(void *p, int bit);
/**
 * Sets specified bit in memory using pointer P and specified bit B to opposite of its current value
 */
extern void bitinv(void *p, int bit);
/**
 * Returns 0 if specified bit in memory using pointer P and specified bit B is 0, else returns non zero int
 */
extern int  bittst(void *p, int bit);

#endif

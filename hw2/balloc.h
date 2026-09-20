#ifndef BALLOC_H
#define BALLOC_H

#include "freelist.h"
#include "bbm.h"

typedef void *Balloc;

/**
 * Creates and returns a Balloc (which points to a BallocData struct pointer,
 * which holds:
 * size_t size;
    int l; -- MUST BE AT LEAST 3 - due to 64 bit memory only letting min
    int u;
    void *mem;
    FreeList fl;
    BBM map;
    )
 * 
 *  Utilizes the mmalloc function to allocate memory. 
 */
extern Balloc bcreate(unsigned int size, int l, int u);
/**
 * Frees a BallocData (pointer pointed to by POOL) from memory,
 * including it's own memory, and free list and buddy bit map.
 */
extern void   bdelete(Balloc pool);

extern void *balloc(Balloc pool, unsigned int size);
extern void  bfree(Balloc pool, void *mem);

extern unsigned int bsize(Balloc pool, void *mem);
extern void bprint(Balloc pool);

#endif

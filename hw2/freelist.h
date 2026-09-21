#ifndef FREELIST_H
#define FREELIST_H

#include <stdlib.h>

typedef void *FreeList;

/**
 * Utilizes maloc to create a 
 */
extern FreeList freelistcreate(size_t size, int l, int u);
extern void     freelistdelete(FreeList f, int l, int u);

extern void *freelistalloc(FreeList f, void *base, int e, int l, int u);
extern void  freelistfree(FreeList f, void *base, void *mem, int e, int l, int u);

// returns e
extern int freelistsize(FreeList f, void *base, void *mem, int l, int u);
extern void freelistprint(FreeList f, int l, int u);

#endif

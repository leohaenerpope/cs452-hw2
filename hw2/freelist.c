#include "freelist.h"

FreeList freelistcreate(size_t size, int l, int u) {
}
void     freelistdelete(FreeList f, int l, int u);

void *freelistalloc(FreeList f, void *base, int e, int l);
void  freelistfree(FreeList f, void *base, void *mem, int e, int l);

int freelistsize(FreeList f, void *base, void *mem, int l, int u);
void freelistprint(FreeList f, int l, int u);
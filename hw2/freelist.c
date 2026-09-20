#include "freelist.h"


typedef struct {
    void **lists;
} *FreeListData;


FreeList freelistcreate(size_t size, int l, int u){

    FreeList f;
    return f;
}
void     freelistdelete(FreeList f, int l, int u);

void *freelistalloc(FreeList f, void *base, int e, int l){
    return NULL;
}
void  freelistfree(FreeList f, void *base, void *mem, int e, int l);

int freelistsize(FreeList f, void *base, void *mem, int l, int u){
    return 0;
}
void freelistprint(FreeList f, int l, int u);
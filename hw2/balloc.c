#include "balloc.h"
#include "stdio.h"
#include "freelist.h"
#include "bbm.h"


typedef struct {
    size_t size;
    int l;
    int u;
    void *mem;
    FreeList fl;
    BBM *map;
} BallocData;


Balloc bcreate(unsigned int size, int l, int u){
    BallocData *b = mmalloc(sizeof(BallocData));
    if (b == NULL) return NULL;
    b->size = size;
    b->l=l;
    b->u=u;

    b->mem = mmalloc(size);
    if (b->mem == NULL) {
        mmfree(b, sizeof(BallocData));
        return NULL;
    }

    b->fl = freelistcreate(size, l, u);
    if (b->fl == NULL) {
        mmfree(b->mem, size);
        mmfree(b, sizeof(BallocData));
        return NULL;
    }

    b->map = mmalloc((u-l+1) * sizeof(BBM));
    if (b->map == NULL) {
        freelistdelete(b->fl, l, u);
        mmfree(b->mem, size);
        mmfree(b, sizeof(BallocData));
        return NULL;
    }

    for (int e = l; e <= u; e++){
        b->map[e-l] = bbmcreate(size, e);
    }

    freelistfree(b->fl, b->mem, b->mem, u, l, u);
    
    return b;
}
void   bdelete(Balloc pool) {
    BallocData *b = pool;

    int amount = b->u - b->l + 1;

    // free up everything
    for (int i = 0; i < amount; i++){
        if (b->map[i] != NULL) bbmdelete(b->map[i]);
    }
    mmfree(b->map, amount * sizeof(BBM));
    freelistdelete(b->fl, b->l, b->u);
    mmfree(b->mem, b->size);
    mmfree(b, sizeof(BallocData));
}

void *balloc(Balloc pool, unsigned int size) {
    BallocData *b = pool;


    int e = size2e(size);
    if (e2size(e) < size) e++;

    // if entered size is too low for mem specified to handle, handle it, switch to l
    if (e < b->l) {
        e = b->l;
        fprintf(stderr, "WARNING: Entered size is too low, memory pool is not specified to handle it. Setting (e) to (l)\n");

    }
    
    // get a block from the free list (that is now not going to be free)
    void *mem = freelistalloc(b->fl, b->mem, e, b->l, b->u);
    if (mem == NULL){
        return NULL;
    }

    // Toggle the bitmap for the specific buddy pair
    int spot = e - b->l;
    if (bbmtst(b->map[spot], b->mem, mem, e)) {
        bbmclr(b->map[spot], b->mem, mem, e);
    } else {
        bbmset(b->map[spot], b->mem, mem, e);
    }

    return mem;
}
void  bfree(Balloc pool, void *mem){
    if (pool == NULL || mem == NULL) return;
    BallocData *b = pool;

    int bytes = bsize(pool, mem);
    if (bytes == 0) {
        fprintf(stderr, "ERROR (bfree): unable to obtain size of memory block\n");
        return;
    }

    int e = size2e(bytes);
    int spot = e - b->l;
    if (bbmtst(b->map[spot], b->mem, mem, e)) {
        bbmclr(b->map[spot], b->mem, mem, e);
    } else {
        bbmset(b->map[spot], b->mem, mem, e);
    }

    freelistfree(b->fl, b->mem, mem, e, b->l, b->u);
}

unsigned int bsize(Balloc pool, void *mem) {
    if (pool == NULL || mem == NULL) return 0;
    BallocData *b = pool;

    size_t offset = (size_t)((char *)mem - (char*)b->mem);

    for (int e = b->l; e <= b->u; e++){
        if (offset % e2size(e) != 0) continue;

        int spot = e - b->l;

        if (bbmtst(b->map[spot], b->mem, mem, e)) return e2size(e);
    }

    return 0;
}
void bprint(Balloc pool);


#include "balloc.h"
#include "stdio.h"


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

    freelistfree(b->fl, b->mem, b->mem, u, l);
    
    return b;
}
void   bdelete(Balloc pool) {
    BallocData *b = pool;

    int amount = b->u - b->l + 1;

    // free up everything
    for (int i = 0; i < amount; i++){
        if (b->map[i] != NULL) bbmdelete(b->map[i]);
    }
    mmfree(b->map, amount);
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
        printf(stderr, "WARNING: Entered size is too low, memory pool is not specified to handle it. Setting (e) to (l)");

    }
    
    // get a block from the free list (that is now not going to be free)
    void *mem = freelistalloc(b->fl, b->mem, e, b->l, b->u);
    if (mem == NULL){
        return NULL;
    }

    // Toggle the bitmap for the specific buddy pair
    int idx = e - b->l;
    if (bbmtst(b->map[idx], b->mem, mem, e)) {
        bbmclr(b->map[idx], b->mem, mem, e);
    } else {
        bbmset(b->map[idx], b->mem, mem, e);
    }

    return mem;
}
void  bfree(Balloc pool, void *mem){
    BallocData *b = pool;


}

unsigned int bsize(Balloc pool, void *mem) {
    return 0;
}
void bprint(Balloc pool);


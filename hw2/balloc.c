#include "balloc.h"


typedef struct {
    size_t size;
    int l;
    int u;
    void *mem;
    FreeList fl;
    BBM map;
} BallocData;


Balloc bcreate(unsigned int size, int l, int u){
    
    BallocData *b = mmalloc(sizeof(BallocData));
    if (b == NULL){
        return NULL;
    }
    b->size = size;
    b->l=l;
    b->u=u;
    b->mem = mmalloc(size);
    if (b->mem == NULL) {
        mmfree(b, sizeof(BallocData));
        return NULL;
    }
    b->fl = freelistcreate(size, l, u);
    b->map = bbmcreate(size, u);
    
    return b;
}

void   bdelete(Balloc pool) {
    BallocData *b = pool;

    bbmdelete(b->map);
    freelistdelete(b->fl, b->l, b->u);
    mmfree(b->mem, b->size);
    mmfree(b, sizeof(BallocData));
}

void *balloc(Balloc pool, unsigned int size) {
    BallocData *b = pool;

    int e = size2e(size);
    if (e2size(e) < size){
        e++;
    }
    
    void *mem = freelistalloc(b->fl, b->mem, e, b->l);
    if (mem == NULL){
        return NULL;
    }

    bbmset(b->map, b->mem, mem, e);

    return mem;
}
void  bfree(Balloc pool, void *mem){
    BallocData *b = pool;


}

unsigned int bsize(Balloc pool, void *mem) {
    return 0;
}
void bprint(Balloc pool);


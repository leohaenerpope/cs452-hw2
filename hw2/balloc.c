#include "balloc.h"

Balloc bcreate(unsigned int size, int l, int u);
void   bdelete(Balloc pool);

void *balloc(Balloc pool, unsigned int size);
void  bfree(Balloc pool, void *mem);

unsigned int bsize(Balloc pool, void *mem);
void bprint(Balloc pool);


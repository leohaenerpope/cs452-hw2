#include <stdlib.h>
#include <string.h>

#include "bm.h"
#include "utils.h"

/**
 * Returns the amount of bits in the bitmap by looking at the bit value amount stored in memory,
 * located sizeof(size_t) behind the actual bitmap memory location
 */
static size_t bmbits(BM b) { size_t *bits=b; return *--bits; }

/**
 * Returns byte amount of a bmbits(b) reult
 */
static size_t bmbytes(BM b) { return bits2bytes(bmbits(b)); }

/**
 * Determines if an index for a bit in the bitmap is within range
 * of the bitmap itself by using bmbits to grab the actual size of the map,
 * and comparing with the specified index.
 */
static void ok(BM b, size_t i) {
  if (i<bmbits(b))
    return;
  fprintf(stderr,"bitmap index out of range\n");
  exit(1);
}         

// Rest of documentation inside of bm.h

extern BM bmcreate(size_t bits) {
  size_t bytes=bits2bytes(bits);
  size_t *p=mmalloc(sizeof(size_t)+bytes);
  if ((long)p==-1)
    return 0;
  *p=bits; // stores bit amount at the size_t space created
  BM b=++p; // then moves and creates the pointer to the actual bitmap in memory
  memset(b,0,bytes);
  return b;
}


extern void bmdelete(BM b) {
  size_t *p=b;
  p--;
  mmfree(p,sizeof(size_t)+bits2bytes(*p)); // sizeof amount of bits info + amount of bits bit map takes
}

extern void bmset(BM b, size_t i) {
  ok(b,i); bitset(b+i/bitsperbyte,i%bitsperbyte);
}

extern void bmclr(BM b, size_t i) {
  ok(b,i); bitclr(b+i/bitsperbyte,i%bitsperbyte);
}

extern int bmtst(BM b, size_t i) {
  ok(b,i); return bittst(b+i/bitsperbyte,i%bitsperbyte); // returns value of the bit
}

extern void bmprt(BM b) {
  for (int byte=bmbytes(b)-1; byte>=0; byte--)
    printf("%02x%s",((char *)b)[byte],(byte ? " " : "\n"));
}

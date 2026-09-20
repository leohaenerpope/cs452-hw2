#include "bbm.h"
#include "bm.h"
#include "utils.h"

/**
 * Returns amount of buddies that are needed to
 * hold amount of bits SIZE in consideration with
 * the known block size exponent e
 */
static size_t mapsize(size_t size, int e) {
  size_t blocksize=e2size(e);
  size_t blocks=divup(size,blocksize);
  size_t buddies=divup(blocks,2);
  return buddies;
}

/**
 * Returns the bitmap specific bit address for storing the buddy information in the bitmap.
 * Given a base memory point, and memory point of a buddy, with size exponent
 */
static size_t bitaddr(void *base, void *mem, int e) {
  size_t addr=baddrclr(base,mem,e)-base; // subtract base again from the baddrclr (which returns the exponent 0 address of the pair)
  size_t blocksize=e2size(e);
  return addr/blocksize/2;
}

// Rest of documentation inside of bbm.h

extern BBM bbmcreate(size_t size, int e) {
  return bmcreate(mapsize(size,e));
}

extern void bbmdelete(BBM b) {
  bmdelete(b);
}

extern void bbmset(BBM b, void *base, void *mem, int e) {
  bmset(b,bitaddr(base,mem,e));
}

extern void bbmclr(BBM b, void *base, void *mem, int e) {
  bmclr(b,bitaddr(base,mem,e));
}

extern int bbmtst(BBM b, void *base, void *mem, int e) {
  return bmtst(b,bitaddr(base,mem,e));
}

extern void bbmprt(BBM b) { bmprt(b); }

extern void *baddrset(void *base, void *mem, int e) {
  unsigned int mask=1<<e; // mask, use or value to set e exponent spot to be 1
  return base+((mem-base)|mask);
}

extern void *baddrclr(void *base, void *mem, int e) {
  unsigned int mask=~(1<<e); // clear, utilizing and with a NOT-ed 000(e)0000 value
  return base+((mem-base)&mask);
}

extern void *baddrinv(void *base, void *mem, int e) {
  unsigned int mask=1<<e; // like the set, utilizing XOR now to just flip the e bit
  return base+((mem-base)^mask);
}

extern int baddrtst(void *base, void *mem, int e) {
  unsigned int mask=1<<e;
  return (mem-base)&mask;
}

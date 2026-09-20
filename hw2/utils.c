#include "utils.h"
#include "sys/mman.h"

// More documentation in utils.h

void *mmalloc(size_t size) {
    void *p = mmap(0, size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1, 0);
    // if (p == MAP_FAILED) return NULL; - may add this
    return p;
}
void mmfree(void *p, size_t size) {
    munmap(p, size);
}

size_t divup(size_t n, size_t d) {
    return (n/d) + (n % d ? 1 : 0);
}
size_t bits2bytes(size_t bits) {
    return divup(bits, 8);
}

size_t e2size(int e) {
    return (size_t)1 << e;
}
int size2e(size_t size) {
    int e = 0;
    while (size > 1){
        size >>= 1;
        e++;
    }
    return e;
}

void bitset(void *p, int bit) {
    unsigned char *bytes = p; // pointer accessor declared as unsigned char - which are conveniently 1 byte long
    int byte = bit / 8;
    int offset = bit % 8;

    bytes[byte] |= (1 << offset);
}
void bitclr(void *p, int bit) {
    unsigned char *bytes = p;
    int byte = bit / 8;
    int offset = bit % 8;

    bytes[byte] &= ~(1 << offset);
}
void bitinv(void *p, int bit) {
    unsigned char *bytes = p;
    int byte = bit / 8;
    int offset = bit % 8;

    bytes[byte] ^= (1 << offset);
}
int  bittst(void *p, int bit){
    unsigned char *bytes = p;
    int byte = bit / 8;
    int offset = bit % 8;

    return bytes[byte] & (1 << offset);
}
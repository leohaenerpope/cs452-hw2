#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "balloc.h"

#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "FAILED: %s\n", msg); \
            exit(1); \
        } else { \
            printf("PASSED: %s\n", msg); \
        } \
    } while(0)

int main(void) {
    printf("Balloc Tests\n");

    // 8 byte min, 1024 byte max
    int l = 3;
    int u = 10;
    unsigned int pool_size = 1 << u;

    printf("\nCreating balloc pool --------------------------\n");
    Balloc pool = bcreate(pool_size, l, u);
    TEST_ASSERT(pool != NULL, "bcreate successfully allocated memory pool");

    printf("\nByte requests --------------------------\n");
    void *p1 = balloc(pool, 1); // this should clamp to 2^3 = 8 bytes
    TEST_ASSERT(p1 != NULL, "balloc(1) returned valid pointer");
    unsigned int sz1 = bsize(pool, p1);
    TEST_ASSERT(sz1 == (1U << l), "bsize returned minimum block size (8 bytes)");

    
    memset(p1, 'A', sz1); // this makes sure memory region is safe to write to

    printf("\nAllocations --------------------------\n");
    void *p2 = balloc(pool, 100); // 100 bytes -> 128 bytes
    TEST_ASSERT(p2 != NULL, "balloc(100) returned valid pointer");
    TEST_ASSERT(bsize(pool, p2) == 128, "bsize(p2) returned 128 bytes");

    void *p3 = balloc(pool, 200); // 200 bytes -> 256 bytes
    TEST_ASSERT(p3 != NULL, "balloc(200) returned valid pointer");
    TEST_ASSERT(bsize(pool, p3) == 256, "bsize(p3) returned 256 bytes");

    TEST_ASSERT(p1 != p2 && p2 != p3 && p1 != p3, "All different pointer spots");

    printf("\nFreeing --------------------------\n");
    bfree(pool, p1);
    bfree(pool, p2);
    bfree(pool, p3);

    // Ensure all split blocks merged back together
    void *p_large = balloc(pool, pool_size);
    TEST_ASSERT(p_large != NULL, "balloc succeeded for full pool size (buddies correctly merged)");
    TEST_ASSERT(bsize(pool, p_large) == pool_size, "bsize returned total pool capacity (1024 bytes)");

    bfree(pool, p_large);

    printf("\nMemory pool out of space tests --------------------------\n");
    void *a1 = balloc(pool, 512);
    void *a2 = balloc(pool, 512);
    TEST_ASSERT(a1 != NULL && a2 != NULL, "Allocated two 512-byte blocks (full capacity)");

    void *a_bad = balloc(pool, 8);
    TEST_ASSERT(a_bad == NULL, "balloc cleanly returned NULL when pool is fully exhausted");

    bfree(pool, a1);
    bfree(pool, a2);

    printf("\nPool deletion --------------------------\n");
    bdelete(pool);
    printf("bdelete executed without errors.\n");

    printf("\nAll tests successfully passed.\n");
    return 0;
}
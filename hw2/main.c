#include <assert.h>
#include <stdio.h>
#include "utils.h"
#include "balloc.h"

int main(void)
{
    assert(divup(10, 3) == 4);
    assert(divup(9, 3) == 3);
    assert(divup(0, 3) == 0);

    assert(bits2bytes(8) == 1);
    assert(bits2bytes(9) == 2);

    assert(e2size(4) == 16);
    assert(e2size(10) == 1024);

    assert(size2e(16) == 4);
    assert(size2e(1024) == 10);

    printf("utils tests passed\n");

    
    return 0;
}
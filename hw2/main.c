#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "balloc.h"
#include "freelist.h"
#include "deq.h"

void freelisttest(void) {
    printf("\n\nFreelist tests\n\n");

    int l = 3;
    int u = 5;
    size_t pool_size = e2size(u);

    void *mem = mmalloc(pool_size);
    assert(mem != NULL);

    FreeList fl = freelistcreate(pool_size, l, u);
    assert(fl != NULL);
    freelistfree(fl, mem, mem, u, l, u);
    printf("initial State (1 block of 32)\n");
    freelistprint(fl, l, u);

    void *p1 = freelistalloc(fl, mem, 3, l, u);
    assert(p1 == mem);
    freelistprint(fl, l, u);
    printf("\n\n");

    void *p2 = freelistalloc(fl, mem, 3, l, u);
    assert(p2 == (char *)mem + 8);
    freelistprint(fl, l, u);
    printf("\n\n");

    void *p3 = freelistalloc(fl, mem, 4, l, u);
    assert(p3 == (char *)mem + 16);
    freelistprint(fl, l, u);
    printf("\n\n");

    printf("This should fail\n");
    void *p_fail = freelistalloc(fl, mem, 3, l, u);
    assert(p_fail == NULL);
    freelistfree(fl, mem, p1, 3, l, u);
    freelistprint(fl, l, u);
    printf("\n\n");

    freelistdelete(fl, l, u);
    mmfree(mem, pool_size);
    printf("\nFreelist tests passed\n\n");
}


int main(void)
{
    // Some tests for utils
    assert(divup(10, 3) == 4);
    assert(divup(9, 3) == 3);
    assert(divup(0, 3) == 0);

    assert(bits2bytes(8) == 1);
    assert(bits2bytes(9) == 2);

    assert(e2size(4) == 16);
    assert(e2size(10) == 1024);

    assert(size2e(16) == 4);
    assert(size2e(1024) == 10);

    printf("\nutils tests passed in main.c\n");

    freelisttest();

    


    // deq - copied from main.c from deq assignment

    Deq q=deq_new();

    // BASIC MAIN TESTING SUITE - Comment/uncomment out individual test sections for unit testing functionality

    // PUT TESTING -------------------------------------------------

    // // head puts
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_head_put(q, "HeadFourthPut");

    // // tail puts
    // deq_tail_put(q, "TailFirstPut");
    // deq_tail_put(q, "TailSecondPut");
    // deq_tail_put(q, "TailThirdPut");
    // deq_tail_put(q, "TailFourthPut");

    // // both head and tail puts 1
    // deq_head_put(q, "HeadFirstPut");
    // deq_tail_put(q, "TailFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_tail_put(q, "TailSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_head_put(q, "HeadFourthPut");
    // deq_tail_put(q, "TailThirdPut");
    // deq_tail_put(q, "TailFourthPut");

    // // both head and tail puts 2
    // deq_tail_put(q, "TailFirstPut");
    // deq_tail_put(q, "TailSecondPut");
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");

    // GET TESTING -------------------------------------------------

    // // get head for a 3-element deq. (HeadThirdPut should be gotten)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_head_get(q);

    // // get tail for a 3-element deq. (HeadFirstPut should be gotten)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_tail_get(q);

    // // get tail for a 3-element deq part 2 (should be empty)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_tail_get(q);
    // deq_tail_get(q);
    // deq_tail_get(q);

    // // get tail on 1-element deq
    // deq_head_put(q, "HeadFirstPut");
    // deq_tail_get(q);

    // // get head on 1-element deq
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_get(q);

    // // get head/tail on 0-element deq (returns 0, nothing happens)
    // deq_head_get(q);
    // deq_tail_get(q);

    // ITH TESTING -------------------------------------------------

    // // head ith - 3 element - index 0 (should print HeadThirdPut)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // printf(deq_head_ith(q, 0));
    // printf("\n");

    // // head ith - 3 element - index 1 (should print HeadSecondPut)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // printf(deq_head_ith(q, 1));
    // printf("\n");

    // // head ith - 3 element - index 2 (should print HeadFirstPut)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // printf(deq_head_ith(q, 2));
    // printf("\n");

    // // head ith - 3 element - index 3 (out of bounds, returns 0)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // Data d = deq_head_ith(q, 3);
    // if (d == 0) {
    //   printf("Returned 0, due to index out of bounds");
    // }
    // printf("\n");

    // // tail ith - 3 element - index 0 (should print HeadFirstPut)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // printf(deq_tail_ith(q, 0));
    // printf("\n");

    // // tail ith - 3 element - index 1 (should print HeadSecondPut)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // printf(deq_tail_ith(q, 1));
    // printf("\n");

    // // tail ith - 3 element - index 2 (should print HeadThirdPut)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // printf(deq_tail_ith(q, 2));
    // printf("\n");

    // // tail ith - 3 element - index 3 (out of bounds, returns 0)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // Data d = deq_tail_ith(q, 3);
    // if (d == 0) {
    //   printf("Returned 0, due to index out of bounds");
    // }
    // printf("\n");

    // // tail ith - 3 element - index -1 (out of bounds, returns 0)
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // Data d = deq_tail_ith(q, -1);
    // if (d == 0) {
    //   printf("Returned 0, due to index out of bounds");
    // }
    // printf("\n");

    // // tail ith - 1 element - index 0 (should print HeadFirstPut)
    // deq_head_put(q, "HeadFirstPut");
    // printf(deq_tail_ith(q, 0));
    // printf("\n");

    // // tail ith - 1 element - index 1 (out of bounds)
    // deq_head_put(q, "HeadFirstPut");
    // Data d = deq_tail_ith(q, -1);
    // if (d == 0) {
    //   printf("Returned 0, due to index out of bounds");
    // }
    // printf("\n");

    // // head ith - 0 element - index 0 (out of bounds)
    // Data d = deq_tail_ith(q, 0);
    // if (d == 0) {
    //   printf("Returned 0, due to index out of bounds");
    // }
    // printf("\n");

    // REM TESTING -------------------------------------------------

    // // head rem - 3 element - HeadFirstPut
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_head_rem(q, "HeadFirstPut");

    // // head rem - 3 element - HeadSecondPut
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_head_rem(q, "HeadSecondPut");

    // // head rem - 3 element - HeadThirdPut
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_head_rem(q, "HeadThirdPut");

    // // tail rem - 3 element - HeadFirstPut
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_tail_rem(q, "HeadFirstPut");

    // // tail rem - 3 element - HeadSecondPut
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_tail_rem(q, "HeadSecondPut");

    // // tail rem - 3 element - HeadThirdPut
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_tail_rem(q, "HeadThirdPut");

    // // tail rem - 3 element - HeadThirdPut, HeadFirstPut
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_tail_rem(q, "HeadThirdPut");
    // deq_tail_rem(q, "HeadFirstPut");

    // // tail rem - 3 element - HeadThirdPut, HeadFirstPut, HeadSecondPut
    // deq_head_put(q, "HeadFirstPut");
    // deq_head_put(q, "HeadSecondPut");
    // deq_head_put(q, "HeadThirdPut");
    // deq_tail_rem(q, "HeadThirdPut");
    // deq_tail_rem(q, "HeadFirstPut");
    // deq_tail_rem(q, "HeadSecondPut");

    // // head rem - duplicates - should now be lfl
    // deq_tail_put(q, "f");
    // deq_tail_put(q, "l");
    // deq_tail_put(q, "f");
    // deq_tail_put(q, "l");
    // deq_head_rem(q, "f");

    // // tail rem - duplicates - should now be fll
    // deq_tail_put(q, "f");
    // deq_tail_put(q, "l");
    // deq_tail_put(q, "f");
    // deq_tail_put(q, "l");
    // deq_tail_rem(q, "f");

    // // tail rem - nothing - size 0
    // Data d = deq_tail_rem(q, "f");
    // if (d == 0) {
    //   printf("Returned 0, due to not being able to remove anything.");
    // }
    // printf("\n");

    // // tail rem - nothing - size 1
    // deq_tail_put(q, "a");
    // Data d = deq_tail_rem(q, "f");
    // if (d == 0) {
    //   printf("Returned 0, due to not being able to remove anything.");
    // }
    // printf("\n");

    // // bigger test - should be zyyyxxa at first - then turned into zyyyxx
    // deq_tail_put(q, "z");
    // deq_tail_put(q, "x");
    // deq_head_put(q, "y");
    // deq_head_put(q, "y");
    // deq_head_put(q, "y");
    // deq_head_put(q, "z");
    // deq_tail_put(q, "x");
    // deq_tail_put(q, "a");
    // printf(deq_head_ith(q, 2)); // print y
    // printf(deq_tail_ith(q, 2)); // print x
    // printf("\n");
    // deq_head_rem(q, "a");
    // deq_tail_rem(q, "z");


    // ------------------------------------------------------------------------------------


    // // valgrind test --------------------------------

    Deq q2 = deq_new();
    deq_tail_put(q2, "z");
    deq_tail_put(q2, "x");
    deq_head_put(q2, "y");
    deq_head_put(q2, "y");
    deq_head_put(q2, "y");
    deq_head_get(q2);
    deq_head_put(q2, "z");
    deq_tail_put(q2, "x");
    deq_tail_put(q2, "a");
    printf("\n");
    deq_head_rem(q2, "a");
    deq_tail_rem(q2, "z");
    char *s2=deq_str(q2,0);
    printf("Deq program output: (Should be z y y x x)\n\n");
    printf("%s\n",s2);
    
    free(s2);
    

    deq_del(q2,0);
    

    // // ---------------------------------------------------- 





    char *s=deq_str(q,0);
    
    printf("%s\n",s);
    
    free(s);

    deq_del(q,0);
    return 0;
}



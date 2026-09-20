#include "freelist.h"


FreeList freelistcreate(size_t size, int l, int u) {
    void **heads = mmalloc((u-l+1) * sizeof(void*));
    for (int i = 0; i < u-l+1; i++){
        heads[i] = NULL;
    }
    return (FreeList)heads;
}
void     freelistdelete(FreeList f, int l, int u) {
    mmfree(f, (u-l+1) * sizeof(void*));
}

void *freelistalloc(FreeList f, void *base, int e, int l, int u){
    if (e < l || e > u) {
        fprintf(stderr, "ERROR: freelistalloc specified e is incorrect for specified memory.");
        return NULL;
    } 

    void **lists = (void **) f;
    int target = e - l;
    
    // if we found the correctly sized block, immediately grab and update head, return the block we got
    if (lists[target] != NULL){
        void *block = lists[target];
        lists[target] = *(void **)block;
        return block;
    }

    int new_e = e+1;

    // go up the free list searching for smallest available block that fits
    while (new_e <= u && lists[new_e-l] == NULL){
        new_e++;
    }
    if (new_e > u) {
        fprintf(stderr, "ERROR: freelistalloc unable to find correct e inside of memory block");
        return NULL;
    }

    // grab the found free block and update list head to either next free block (of the current size) or null
    void *block = lists[new_e-l];
    lists[new_e-l] = *(void **)block;

    // now, we will split the block into buddies, keep grabbing the left most 
    while (new_e > e) {
        new_e--;

        void *right = (char *) block + e2size(new_e);
        int spot = new_e - l;

        *(void **)right = lists[spot]; // right->next = current list head
        lists[spot] = right; // current list head = right   
    }

    // finally, return the now non-free memory block spot that we are going to put data into
    return block;

}
void  freelistfree(FreeList f, void *base, void *mem, int e, int l, int u) {
    if (e < l) {
        fprintf(stderr, "ERROR: freelistalloc specified e is incorrect for specified memory.");
        return;
    }

    void **lists = (void **) f;

    // repeatedly connects buddy blocks together (multiple if freelist setup allows) to kind of "reset" the freelist
    while (e < u) {
        void* buddy = baddrinv(base, mem, e);
        int target = e - l;
        void *curr = lists[target];
        void *prev = NULL;
        int found = 0;

        // find buddy in the certain size list
        while (curr != NULL){
            if (curr == buddy) {
                found = 1;
                break;
            }
            prev = curr;
            curr = *(void**) curr; //next free list block in free list (for specified size)
        }
        if (!found) break; // stop if nothing is found as a buddy of this block

        if (prev == NULL) {
            lists[target] =  *(void**) buddy; // update list head to now point at block after buddy - buddy was at head
        } else {
            *(void**) prev = *(void**) buddy; // connect block before buddy to whatever is after buddy
        }

        if (buddy < mem) mem = buddy; // want to be at the lower address

        e++;
    }

    int target = e-l;
    *(void**) mem = lists[target]; // update the now free block to point to current (specific size) list head
    lists[target] = mem; // free list (specific size) head now is the mem point
}

int freelistsize(FreeList f, void *base, void *mem, int l, int u){
    return 0;
}
void freelistprint(FreeList f, int l, int u);
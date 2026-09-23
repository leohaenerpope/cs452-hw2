#include "freelist.h"
#include "stdio.h"
#include "utils.h"
#include "bbm.h"

int freelistisbuddyfree(FreeList f, void *base, void *mem, int e, int l) {
    if (f == NULL || base == NULL || mem == NULL) return 0;

    void **lists = (void **) f;
    void *buddy = baddrinv(base, mem, e);
    void *curr = lists[e - l];

    while (curr != NULL) {
        if (curr == buddy) return 1;
        curr = *(void **) curr;
    }

    return 0;
}

// More documentation inside of freelist.h

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
        fprintf(stderr, "ERROR: freelistalloc specified e is incorrect for specified memory.\n");
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
        fprintf(stderr, "ERROR: freelistalloc unable to find correct e inside of memory block. Space is probably limited.\n");
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
    if (f == NULL || mem == NULL) {
        fprintf(stderr, "ERROR: NULL value given in freelistfree\n");
        return;
    } else if (e < l || e > u) {
        fprintf(stderr, "ERROR: Specified e is incorrect for specified memory. freelistfree\n");
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
    if (f == NULL || base == NULL || mem == NULL) return 0;

    void **lists = (void **) f;
    size_t offset = (size_t)((char *)mem - (char *)base);
    
    for (int e = l; e < u; e++){
        if (offset % e2size(e) != 0) continue; // gotta be aligned in the correct e size - a little faster
        
        void *buddy = baddrinv(base, mem, e);
        int spot = e-l;
        void *curr = lists[spot];

        while (curr != NULL){
            if (curr == buddy) return e; //found buddy, return e
            curr = *(void**) curr; 
        }
    }

    return u;
}
void freelistprint(FreeList f, int l, int u) { // may want to use the freelistsize function here?
    if (f == NULL) return;

    void **lists = (void **) f;

    for (int e = l; e <= u; e++) {
        int spot = e-l;
        void *curr = lists[spot];


        fprintf(stdout, "Blocks of order %2d (size %8zu): ", e, e2size(e));
        if (curr == NULL) {
            fprintf(stdout, " {empty}\n");
            continue;
        }

        while (curr != NULL) {
            fprintf(stdout, " -> %p", curr);
            curr = *(void **)curr; // next
        }
        fprintf(stdout, "\n");
    }
}
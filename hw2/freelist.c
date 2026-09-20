#include "freelist.h"


FreeList freelistcreate(size_t size, int l, int u) {
    int num_lists = u - l + 1;
    void **heads = mmalloc(num_lists * sizeof(void*));
    for (int i = 0; i < num_lists; i++){
        heads[i] = NULL;
    }
    return (FreeList)heads;
}
void     freelistdelete(FreeList f, int l, int u) {
    int num_lists = u - l + 1;
    mmfree(f, num_lists * sizeof(void*));
}

void *freelistalloc(FreeList f, void *base, int e, int l, int u){
    void **lists = (void **) f;
    int target = e - l;
    
    if (lists[target] != NULL){
        void *block = lists[target];
        lists[target] = *(void **)block;
        return block;
    }

    int new_e = e+1;

    while (new_e <= u && lists[new_e-l] == NULL){
        new_e++;
    }
    if (new_e > u) return NULL;

    void *block = lists[new_e-l];
    lists[new_e-l] = *(void **)block;

    while (new_e > e) {
        new_e--;

        void *right = (char *) block + e2size(new_e);

        int split = new_e - l;
        *(void **)right = lists[split];
        lists[split] = right;
    }

    return block;

}
void  freelistfree(FreeList f, void *base, void *mem, int e, int l);

int freelistsize(FreeList f, void *base, void *mem, int l, int u){
    return 0;
}
void freelistprint(FreeList f, int l, int u);
#ifndef H_HEAP
#define H_HEAP

#define BH_KEY_TYPE int
#define BH_VALUE_TYPE int
#define BH_COMPARE(a,b) (a < b ? -1 : (a > b ? 1 : 0))
#define BH_DISPOSE_KEY(k)
#define BH_DISPOSE_VALUE(v)

typedef struct bheap bheap;
 
bheap *bheap_new_alloc(int size);
void bheap_add(bheap *heap, BH_KEY_TYPE key, BH_VALUE_TYPE value);
BH_KEY_TYPE bheap_pop(bheap *);
BH_VALUE_TYPE bheap_popval(bheap *);
#define bheap_removefirst(h) BH_DISPOSE_KEY(bheap_pop(h))
BH_KEY_TYPE bheap_peek(bheap *);
BH_VALUE_TYPE bheap_peekval(bheap *);
void bheap_del(bheap *heap, BH_KEY_TYPE key);
void bheap_dispose(bheap *heap);


#endif
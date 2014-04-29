#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

#define LEFT(a) 2 * (a)
#define RIGHT(a) 2 * (a) + 1
#define PARENT(a) (a) / 2
#define FIRST 1
#define SWAP(data, a, b, tmp) tmp = data[a]; data[a] = data[b]; data[b] = tmp

typedef struct bhkeyval {
    BH_KEY_TYPE key;
    BH_VALUE_TYPE value;
} bhkeyval;

struct bheap {
    unsigned int size; // Size of the allocated memory (in number of items)
    unsigned int count; // Count of the elements in the heap
    bhkeyval *data; // Array with the elements
};

bheap *bheap_new(int size)
{
	bheap *heap = malloc(sizeof(bheap));
	heap->size = size;
	heap->count = 0;
	heap->comparer = comparer;
	heap->data = malloc(sizeof(bhkeyval) * (size + 1));

	return heap;
}

static void heapify(bheap *heap, int i)
{
	bhkeyval *data = heap->data;
    bhkeyval tmp;
    
	int count = heap->count;
	int left, right, swap;

	while (i < count) {
		left = LEFT(i);

		if (left > count)
			break;

		swap = i;

		if (heap->comparer(heap->data[i], heap->data[left]) > 0)
			swap = left;

		right = RIGHT(i);

		if (right <= count && heap->comparer(heap->data[right], heap->data[swap]) < 0)
			swap = right;

		if (swap == i)
			break;

		SWAP(data, swap, i, tmp);
		i = swap;
	}
}

void bheap_add(bheap *heap, BH_KEY_TYPE key, BH_VALUE_TYPE value)
{
	int c = heap->count + 1, p;
	bhkeyval *data = heap->data;
    bhkeyval tmp;

    data[c].key = key;
	data[c].value = value;

	p = PARENT(c);
	while (p > 0) {
		if (BH_COMPARE(data[p].key, data[c].key) < 0)
			break;
		else
			SWAP(data, p, c, tmp);
		c = p;
		p = PARENT(p);
	}

	heap->count++;
}

BH_KEY_TYPE bheap_pop(bheap *heap)
{
	BH_KEY_TYPE ret;
    bhkeyval *data = heap->data;

	if (heap->count == 0)
		return NULL;

	ret = data[FIRST].key;
    BH_DISPOSE_VALUE(data[FIRST].value);
	data[FIRST] = data[heap->count];
	heapify(heap, FIRST);
	heap->count--;
    
	return ret;
}

BH_VALUE_TYPE bheap_popval(bheap *heap)
{
	BH_VALUE_TYPE ret;
    bhkeyval *data = heap->data;
    
	if (heap->count == 0)
		return NULL;
    
	ret = data[FIRST].value;
    BH_DISPOSE_KEY(data[FIRST].key);
	data[FIRST] = data[heap->count];
	heapify(heap, FIRST);
	heap->count--;
    
	return ret;
}

BH_KEY_TYPE bheap_peek(bheap *heap)
{
	return heap->data[FIRST].key;
}

BH_VALUE_TYPE bheap_peekval(bheap *heap)
{
    return heap->data[FIRST].value;
}

void bheap_del(bheap *heap, BH_KEY_TYPE key)
{
    bhkeyval *data = heap->data;
    int count = heap->count;
	int i;

	for (i = FIRST; i <= count; ++i)
		if (key == data[i].key)
			break;

	if (i > count)
		return;

	data[i] = data[count];
	heapify(heap, i);
	heap->count--;
}

void bheap_dispose(bheap *heap)
{
    int i;
    
    for (i = 0; i < heap->count; ++i) {
        BH_DISPOSE_KEY(heap->data[i].key);
        BH_DISPOSE_VALUE(heap->data[i].value);
    }
    
	free(heap->data);
	free(heap);
}
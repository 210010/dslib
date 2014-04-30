/* The MIT License(MIT)
 
 Copyright(c) 2014 Kang Min Yoo
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files(the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions :
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE. */

#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

#define LEFT(a) 2 * (a)
#define RIGHT(a) 2 * (a) + 1
#define PARENT(a) (a) / 2
#define FIRST 1
#define SWAP(data, a, b, tmp) tmp = data[a]; data[a] = data[b]; data[b] = tmp

struct bheap {
	int(*compare)(void *, void *);
	void(*dispose_key)(void *);
	void(*dispose_value)(void *);
    unsigned int size; // Size of the allocated memory (in number of items)
    unsigned int count; // Count of the elements in the heap
    keyval *data; // Array with the elements
};

bheap *bheap_new(int size, int(*compare)(void *, void *), void(*dispose_key)(void *), void(*dispose_value)(void *))
{
	bheap *heap = malloc(sizeof(bheap));
	heap->size = size;
	heap->count = 0;
	heap->data = malloc(sizeof(keyval) * (size + 1));
	heap->compare = compare;
	heap->dispose_key = dispose_key;
	heap->dispose_value = dispose_value;

	return heap;
}

static void heapify(bheap *heap, int i)
{
	keyval *data = heap->data;
    keyval tmp;
    
	int count = heap->count;
	int left, right, swap;

	while (i < count) {
		left = LEFT(i);

		if (left > count)
			break;

		swap = i;

		if (heap->compare(heap->data[i].key, heap->data[left].key) > 0)
			swap = left;

		right = RIGHT(i);

		if (right <= count && heap->compare(heap->data[right].key, heap->data[swap].key) < 0)
			swap = right;

		if (swap == i)
			break;

		SWAP(data, swap, i, tmp);
		i = swap;
	}
}

void bheap_add(bheap *heap, void *key, void *value)
{
	int c = heap->count + 1, p;
	keyval *data = heap->data;
    keyval tmp;

    data[c].key = key;
	data[c].value = value;

	p = PARENT(c);
	while (p > 0) {
		if (heap->compare(data[p].key, data[c].key) < 0)
			break;
		else
			SWAP(data, p, c, tmp);
		c = p;
		p = PARENT(p);
	}

	heap->count++;
}

keyval bheap_pop(bheap *heap)
{
	keyval ret;
    keyval *data = heap->data;
    
	ret = data[FIRST];
	data[FIRST] = data[heap->count];
	heapify(heap, FIRST);
	heap->count--;
    
	return ret;
}

keyval bheap_peek(bheap *heap)
{
	return heap->data[FIRST];
}

void bheap_del(bheap *heap, void *key)
{
    keyval *data = heap->data;
    int count = heap->count;
	int i;

	for (i = FIRST; i <= count; ++i)
		if (heap->compare(key, data[i].key))
			break;

	if (i > count)
		return;

	data[i] = data[count];
	heapify(heap, i);
	heap->count--;
}

void bheap_dispose(bheap *heap)
{
    unsigned int i;
    
    for (i = 0; i < heap->count; ++i) {
        heap->dispose_key(heap->data[i].key);
        heap->dispose_value(heap->data[i].value);
    }
    
	free(heap->data);
	free(heap);
}
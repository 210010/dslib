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

#ifndef H_HEAP
#define H_HEAP

#include "dslib.h"

typedef struct bheap bheap;
 
bheap *bheap_new_alloc(int, int (*compare)(void *, void *), void (*dispose_key)(void *), void (*dispose_value)(void *));
void bheap_add(bheap *heap, void *key, void *value);
keyval bheap_pop(bheap *);
keyval bheap_peek(bheap *);
void bheap_del(bheap *heap, void *key);
void bheap_dispose(bheap *heap);


#endif
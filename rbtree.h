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

#ifndef H_RBTREE
#define H_RBTREE

#include "dslib.h"

typedef struct rbtree rbtree;
typedef struct rbiterator rbiter;

rbtree *rbtree_new(int (*compare)(void *, void *), void (*dispose_key)(void *), void (*dispose_value)(void *));
void rbtree_add(rbtree *, void *key, void *value);
void rbtree_del(rbtree *, void *key);
void rbtree_dispose(rbtree *);
int rbtree_contains(rbtree *, void *);
int rbtree_count(rbtree *);
void *rbtree_get(rbtree *, void *key);
keyval rbtree_first(rbtree *);
keyval rbtree_last(rbtree *);

rbiter *rbiter_first(rbtree *);
rbiter *rbiter_last(rbtree *);
rbiter *rbiter_next(rbtree *, rbiter *);
rbiter *rbiter_prev(rbtree *, rbiter *);
keyval rbiter_keyval(rbiter *);

#define rbtree_foreach(tree, iter) \
	for (iter = rbiter_first(tree); iter; iter = rbiter_next(tree, iter))
#define rbtree_foreach_reverse(tree, iter) \
	for (iter = rbiter_last(tree); iter; iter = rbiter_prev(tree, iter))

#endif
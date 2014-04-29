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

#define RB_KEY_TYPE int
#define RB_VALUE_TYPE int
#define RB_COMPARE(x, y) (x < y ? -1 : (x > y ? 1 : 0))
#define RB_DISPOSE_KEY(key) 
#define RB_DISPOSE_VALUE(value)

typedef struct rbtree rbtree;
typedef struct rbiterator rbiter;

rbtree *rbtree_new(void);
void rbtree_add(rbtree *, RB_KEY_TYPE key, RB_VALUE_TYPE value);
void rbtree_del(rbtree *, RB_KEY_TYPE key);
void rbtree_dispose(rbtree *);
int rbtree_contains(rbtree *, RB_KEY_TYPE);
int rbtree_count(rbtree *);
RB_VALUE_TYPE rbtree_get(rbtree *, RB_KEY_TYPE key);

rbiter *rbiter_first(rbtree *);
rbiter *rbiter_last(rbtree *);
rbiter *rbiter_next(rbtree *, rbiter *);
rbiter *rbiter_prev(rbtree *, rbiter *);
RB_KEY_TYPE rbiter_key(rbiter *);
RB_VALUE_TYPE rbiter_value(rbiter *);

#define rbtree_foreach(tree, iter) \
	for (iter = rbiter_first(tree); iter; iter = rbiter_next(tree, iter))
#define rbtree_foreach_reverse(tree, iter) \
	for (iter = rbiter_last(tree); iter; iter = rbiter_prev(tree, iter))

#endif
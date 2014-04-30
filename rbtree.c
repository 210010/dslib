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
#include "rbtree.h"

typedef struct rbnode {
	keyval keyval;
	int red;
	struct rbnode *left;
	int left_count;
	struct rbnode *right;
	int right_count;
	struct rbnode *parent;
} rbnode;

struct rbtree {
    int (*compare)(void *, void *);
    void (*dispose_key)(void *);
    void (*dispose_value)(void *);
	rbnode *root;
	int count;
};

static rbnode nil;
static void rbtree_leftrotate(rbtree *tree, rbnode *x);
static void rbtree_rightrotate(rbtree *tree, rbnode *x);
static void rbtree_treeinserthelp(rbtree *tree, rbnode *z);
static rbnode *rbtree_after(rbtree *tree, rbnode *x);
static rbnode *rbtree_before(rbtree *tree, rbnode *x);
static void rbtree_treedesthelper(rbtree *tree, rbnode *x);
static rbnode *rbtree_query(rbtree *tree, void *key);
static void rbtree_deletefixup(rbtree *tree, rbnode *x);

/* private functions */
static void rbtree_leftrotate(rbtree *tree, rbnode *x)
{
	rbnode *y;

	y = x->right;
	x->right = y->left;

	if (y->left != &nil)
		y->left->parent = x;

	y->parent = x->parent;

	if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

static void rbtree_rightrotate(rbtree *tree, rbnode *y)
{
	rbnode *x;

	x = y->left;
	y->left = x->right;

	if (&nil != x->right) x->right->parent = y;

	x->parent = y->parent;

	if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}

static void rbtree_treeinserthelp(rbtree *tree, rbnode *z)
{
	/*  This function should only be called by InsertRBTree (see above) */
	rbnode *x;
	rbnode *y;

	z->left = z->right = &nil;
	y = tree->root;
	x = tree->root->left;

	while (x != &nil) {
		y = x;
		if (tree->compare(x->keyval.key, z->keyval.key) == 1) { /* x.key > z.key */
			x = x->left;
		} else { /* x,key <= z.key */
			x = x->right;
		}
	}
	z->parent = y;
	if (y == tree->root || tree->compare(y->keyval.key, z->keyval.key) == 1) { /* y.key > z.key */
		y->left = z;
	} else {
		y->right = z;
	}
}

static rbnode *rbtree_after(rbtree *tree, rbnode *x)
{
	rbnode *y;
	rbnode *root = tree->root;

	if (&nil != (y = x->right)) { /* assignment to y is intentional */
		while (y->left != &nil) { /* returns the minium of the right subtree of x */
			y = y->left;
		}
		return (y);
	} else {
		y = x->parent;
		while (x == y->right) { /* sentinel used instead of checking for &nil */
			x = y;
			y = y->parent;
		}
		if (y == root) 
			return (&nil);
		return (y);
	}
}

static rbnode *rbtree_before(rbtree *tree, rbnode *x)
{
	rbnode *y;
	rbnode *root = tree->root;

	if (&nil != (y = x->left)) { /* assignment to y is intentional */
		while (y->right != &nil) { /* returns the maximum of the left subtree of x */
			y = y->right;
		}
		return (y);
	} else {
		y = x->parent;
		while (x == y->left) {
			if (y == root) return (&nil);
			x = y;
			y = y->parent;
		}
		return (y);
	}
}

static void rbtree_treedesthelper(rbtree *tree, rbnode *x)
{
	if (x != &nil) {
		rbtree_treedesthelper(tree, x->left);
		rbtree_treedesthelper(tree, x->right);
		tree->dispose_key(x->keyval.key);
		tree->dispose_value(x->keyval.value);
		free(x);
	}
}

static rbnode *rbtree_query(rbtree *tree, void *key)
{
	rbnode *x = tree->root->left;

	if (x == &nil)
		return NULL;

	while (tree->compare(x->keyval.key, key) != 0) {
		if (tree->compare(x->keyval.key, key) == 1)
			x = x->left;
		else
			x = x->right;

		if (x == &nil)
			return NULL;
	}

	return x;
}

static void rbtree_deletefixup(rbtree *tree, rbnode *x)
{
	rbnode *root = tree->root->left;
	rbnode *w;

	while ((!x->red) && (root != x)) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->red) {
				w->red = 0;
				x->parent->red = 1;
				rbtree_leftrotate(tree, x->parent);
				w = x->parent->right;
			}
			if ((!w->right->red) && (!w->left->red)) {
				w->red = 1;
				x = x->parent;
			} else {
				if (!w->right->red) {
					w->left->red = 0;
					w->red = 1;
					rbtree_rightrotate(tree, w);
					w = x->parent->right;
				}
				w->red = x->parent->red;
				x->parent->red = 0;
				w->right->red = 0;
				rbtree_leftrotate(tree, x->parent);
				x = root; /* this is to exit while loop */
			}
		} else { /* the code below is has left and right switched from above */
			w = x->parent->left;
			if (w->red) {
				w->red = 0;
				x->parent->red = 1;
				rbtree_rightrotate(tree, x->parent);
				w = x->parent->left;
			}
			if ((!w->right->red) && (!w->left->red)) {
				w->red = 1;
				x = x->parent;
			} else {
				if (!w->left->red) {
					w->right->red = 0;
					w->red = 1;
					rbtree_leftrotate(tree, w);
					w = x->parent->left;
				}
				w->red = x->parent->red;
				x->parent->red = 0;
				w->left->red = 0;
				rbtree_rightrotate(tree, x->parent);
				x = root; /* this is to exit while loop */
			}
		}
	}
	x->red = 0;
}

/* public functions */
rbtree *rbtree_new(int (*compare)(void *, void *), void (*dispose_key)(void *), void (*dispose_value)(void *))
{
	rbtree *tree;
	rbnode *temp;

	tree = (rbtree *)malloc(sizeof (rbtree));

	if (nil.left != &nil) {
		nil.left = &nil;
		nil.right = &nil;
		nil.parent = &nil;
		nil.red = 0;
		nil.keyval.key = 0;
		nil.keyval.value = 0;
	}

	temp = tree->root = (rbnode *)malloc(sizeof (rbnode));
	temp->parent = temp->left = temp->right = &nil;
	temp->keyval.key = 0;
	temp->keyval.value = 0;
	temp->red = 0;

	tree->count = 0;
    tree->compare = compare;
    tree->dispose_key = dispose_key;
    tree->dispose_value = dispose_value;

	return tree;
}

void rbtree_add(rbtree *tree, void *key, void *value)
{
	rbnode *y;
	rbnode *x;
	rbnode *new_node;

	x = (rbnode *)malloc(sizeof (rbnode));
	x->keyval.key = key;
	x->keyval.value = value;
	x->left_count = 0;
	x->right_count = 0;
	tree->count++;

	rbtree_treeinserthelp(tree, x);
	new_node = x;
	x->red = 1;
	while (x->parent->red) { /* use sentinel instead of checking for root */
		if (x->parent == x->parent->parent->left) {

			y = x->parent->parent->right;

			if (y->red) {

				x->parent->red = 0;
				y->red = 0;
				x->parent->parent->red = 1;
				x = x->parent->parent;

			} else {

				if (x == x->parent->right) {
					x = x->parent;
					rbtree_leftrotate(tree, x);
				}

				x->parent->red = 0;
				x->parent->parent->red = 1;
				rbtree_rightrotate(tree, x->parent->parent);
			}
		} else { /* case for x->parent == x->parent->parent->right */
			y = x->parent->parent->left;

			if (y->red) {

				x->parent->red = 0;
				y->red = 0;
				x->parent->parent->red = 1;
				x = x->parent->parent;

			} else {

				if (x == x->parent->left) {
					x = x->parent;
					rbtree_rightrotate(tree, x);
				}
				x->parent->red = 0;
				x->parent->parent->red = 1;
				rbtree_leftrotate(tree, x->parent->parent);
			}
		}
	}

	tree->root->left->red = 0;
}

void rbtree_del(rbtree *tree, void *key)
{
	rbnode *y;
	rbnode *x;
	rbnode *root = tree->root;
	rbnode *z;

	tree->count--;

	z = rbtree_query(tree, key);

	if (!z)
		return;

	y = ((z->left == &nil) || (z->right == &nil)) ? z : rbtree_after(tree, z);
	x = (y->left == &nil) ? y->right : y->left;
	if (root == (x->parent = y->parent)) { /* assignment of y->p to x->p is intentional */
		root->left = x;
	} else {
		if (y == y->parent->left) {
			y->parent->left = x;
		} else {
			y->parent->right = x;
		}
	}
	if (y != z) {

		if (!(y->red)) rbtree_deletefixup(tree, x);

		y->left = z->left;
		y->right = z->right;
		y->parent = z->parent;
		y->red = z->red;
		z->left->parent = z->right->parent = y;
		if (z == z->parent->left) {
			z->parent->left = y;
		} else {
			z->parent->right = y;
		}
		tree->dispose_key(z->keyval.key);
		tree->dispose_value(z->keyval.value);
		free(z);
	} else {
		if (!(y->red))
			rbtree_deletefixup(tree, x);
		tree->dispose_key(z->keyval.key);
		tree->dispose_value(z->keyval.value);
		free(y);
	}

	return;
}

void rbtree_dispose(rbtree *tree)
{
	rbtree_treedesthelper(tree, tree->root->left);
	free(tree->root);
	free(tree);
}

void *rbtree_get(rbtree *tree, void *key)
{
	return rbtree_query(tree, key)->keyval.value;
}

int rbtree_contains(rbtree *tree, void *key)
{
    return rbtree_query(tree, key) != NULL;
}

int rbtree_count(rbtree *tree)
{
	return tree->count;
}

rbiter *rbiter_first(rbtree *tree)
{
	rbnode *node;

	if (tree->count <= 0)
		return NULL;

	node = tree->root->left;

	while (node->left != &nil)
		node = node->left;

	return (rbiter *)node;
}

rbiter *rbiter_next(rbtree *tree, rbiter *iter)
{
	rbnode *node;

	return (rbiter *)((node = rbtree_after(tree, (rbnode *)iter)) == &nil ? NULL : node);
}

rbiter *rbiter_prev(rbtree *tree, rbiter *iter)
{
	rbnode *node;

	return (rbiter *)((node = rbtree_before(tree, (rbnode *)iter)) == &nil ? NULL : node);
}

keyval rbiter_key(rbiter *iter)
{
	return ((rbnode *)iter)->keyval;
}

rbiter *rbiter_last(rbtree *tree)
{
	rbnode *node;

	if (tree->count <= 0)
		return NULL;

	node = tree->root->left;

	while (node->right != &nil)
		node = node->right;

	return (rbiter *)node;
}

keyval rbiter_keyval(rbiter *iter)
{
	return ((rbnode *)iter)->keyval;
}
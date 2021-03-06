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

#include "rbtree.h"
#include "hash.h"
#include "dslib.h"

void test_rbtree(void)
{
	rbtree *tree;
	rbiter *it;
	int i;

	tree = rbtree_new(&compare_int, &null_func, &null_func);

	for (i = 0; i < 100; ++i)
		rbtree_add(tree, i, 30 + i);

	printf("added count: %i\n", rbtree_count(tree));

	printf("items:\n");
	rbtree_foreach(tree, it){
		printf("%i\t%i\n", rbiter_keyval(it).key, rbiter_keyval(it).value);
	}

	for (i = 0; i < 100; ++i)
		rbtree_del(tree, i);

	printf("final count: %i\n", rbtree_count(tree));
}

static int hash(void *key)
{
	return (int)key;
}

void test_hash(void)
{
	hmap *map = hmap_new(512, &hash, &null_func, &null_func);
	int i;

	for (i = 0; i < 100; ++i)
		hmap_add(map, i, i + 30);

	printf("added count:%i\n", hmap_count(map));

	printf("items:\n");
	for (i = 0; i < 100; ++i)
		printf("%i\t%i\n", i, hmap_get(map, i));

	for (i = 0; i < 100; ++i)
		hmap_del(map, i);
	printf("final count:%i\n", hmap_count(map));
}
int main(void)
{
	test_rbtree();
	test_hash();
}
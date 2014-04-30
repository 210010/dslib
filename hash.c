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
#include <string.h>
#include "hash.h"
#include "rbtree.h"

struct hashmap {
	int(*hash)(void *key);
	void(*dispose_key)(void *);
	void(*dispose_value)(void *);
    int size;
    int count;
    rbtree **data;
};

hmap *hmap_new(int size, int(*hash)(void *key), void(*dispose_key)(void *), void(*dispose_value)(void *))
{
    hmap *map = (hmap *)malloc(sizeof(hmap));
    map->data = (rbtree **)malloc(sizeof(rbtree *) * size);
    memset(map->data, 0, sizeof(rbtree *) * size);
    map->count = 0;
    map->size = size;
	map->dispose_key = dispose_key;
	map->dispose_value = dispose_value;
	map->hash = hash;
    
    return map;
}

void hmap_dispose(hmap *map)
{
	int i;

	for (i = 0; i < map->size; ++i)
	if (map->data[i])
		rbtree_dispose(map->data[i]);

	free(map);
}

void hmap_add(hmap *map, void *key, void *value)
{
    int hash, index;
    
    hash = map->hash(key);
    index = hash % map->size;
    
    if (!map->data[index])
        map->data[index] = rbtree_new(&compare_int, &null_func, map->dispose_value);
    
    rbtree_add(map->data[index], hash, value);

	map->count++;
}

void hmap_del(hmap *map, void *key)
{
    int hash, index;
    
    hash = map->hash(key);
    index = hash % map->size;
    
    rbtree_del(map->data[index], hash);
	map->dispose_key(key);
	map->count--;
	map->data[index] = NULL;
}

int hmap_contains(hmap *map, void *key)
{
    int hash, index;
    
    hash = map->hash(key);
    index = hash % map->size;
    
    return rbtree_contains(map->data[index], hash);
}

int hmap_count(hmap *map)
{
    return map->count;
}

void *hmap_get(hmap *map, void *key)
{
    return rbtree_get(map->data[map->hash(key) % map->size], map->hash(key));
}
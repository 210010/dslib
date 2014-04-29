#ifndef H_HASH
#define H_HASH

#define HM_KEY_TYPE int
#define HM_VALUE_TYPE int
#define HM_HASH(k) k
#define HM_DISPOSE_KEY(k)
#define HM_DISPOSE_VALUE(k)

typedef struct hashmap hmap;

hmap *hmap_new(int);
void hmap_add(hmap *, HM_KEY_TYPE key, HM_VALUE_TYPE value);
void hmap_del(hmap *, HM_KEY_TYPE key);
int hmap_contains(hmap *, HM_KEY_TYPE key);
int hmap_count(hmap *);
HM_VALUE_TYPE hmap_get(hmap *, HM_KEY_TYPE key);

#endif
#ifndef H_DSLIB
#define H_DSLIB

typedef struct {
	void *key;
	void *value;
} keyval;

#define get_struct(ptr, type, member) \
	((type *)((char *)(ptr)–(unsigned long)(&((type *)0)->member)))

#endif
#include "dslib.h"

int compare_int(void *a, void *b)
{
	return ((int)a) < ((int)b) ? -1 : (((int)a) > ((int)b) ? 1 : 0);
}

void null_func(void *a)
{

}
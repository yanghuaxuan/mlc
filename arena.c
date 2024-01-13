#include "arena.h"

#include <stdlib.h>

#define ARENA_DEFAULT_CAPACITY 1024 * 10000

void* aalloc(struct arena* a, size_t size) 
{
	if (a->used + size > a->capacity) {
		a->capacity += (size > ARENA_DEFAULT_CAPACITY) ? 
			size : ARENA_DEFAULT_CAPACITY;
		a->data = realloc(a->data, a->capacity);
		if (a->data == NULL) 
			exit(1);
	}
	a->used += size;
	return (void *)(a->data + a->used - size);
}

void afree(struct arena* a) 
{
	free(a);
}

struct arena* anew() 
{
	struct arena* a = malloc(sizeof(*a) + ARENA_DEFAULT_CAPACITY);
	if (a == NULL)
		return NULL;
	a->used = 0;
	a->capacity = ARENA_DEFAULT_CAPACITY;
	a->data = (char *)a + sizeof(*a);

	return a;
}


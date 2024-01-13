#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

 struct arena {
    size_t used, capacity;
    char* data;
};

/* Allocate size bytes of memory from arena */
void* aalloc(struct arena* arena, size_t size);
/* Destroy arena */
void afree(struct arena* arena);
struct arena* anew();

#endif

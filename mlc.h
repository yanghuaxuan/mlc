#ifndef MLC_H
#define MLC_H

#include "arena.h"
#include <stddef.h>

struct layer {
	size_t weights;
	float bias;
	float (*activate)(float val);
	float w[];
};

struct nn {
	size_t layers;
	struct layer** l;
};

struct layer* laynew(struct arena* arena, size_t weights, float (*activate)(float val));

struct nn* neunew(struct arena* arena, struct layer** layers);

// /* Calculate MSE */
// float cost(int x, int y);
// 
// float grad(int x, int y)

// void forward();

/* Perform sigmoid */
float activate(float val);

#endif

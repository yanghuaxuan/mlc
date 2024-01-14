#include "mlc.h"
#include "arena.h"

#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

static inline float randf() {
	return (float)((double)rand() / RAND_MAX);
}

//struct nn* neunew(struct arena* arena) {
//	aalloc(arena, );
//}
//
struct layer* laynew(struct arena* arena, size_t weights, float (*activate)(float)) {
	struct layer* l = aalloc(arena, sizeof(*l) + sizeof(float) * weights);
	if (!l)
		return NULL;
	l->weights = weights;
	l->bias = randf();
	l->activate = activate;
	for (size_t i = 0; i < weights; i++) {
		l->w[i] = randf();
	}

	return l;
}

struct layer** sequential(struct arena* arena, size_t layers, ...) {
	struct layer** l = aalloc(arena, sizeof(*l) * layers);
	if (!l)
		return NULL;
	va_list ap;
	va_start(ap, layers);
		for (size_t i = 0; i < layers; i++) {
			l[i] = va_arg(ap, struct layer*);
		}
	va_end(ap);

	return l;
}

struct nn* neunew(struct arena* arena, size_t layers, struct layer** l) {
	struct nn* n = aalloc(arena, sizeof(*n));
	n->layers = layers;
	n->l = l;
	return n;
}

float activate(float val) {
	return 1 / (1 + expf(val));
}

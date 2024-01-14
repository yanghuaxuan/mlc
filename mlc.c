#include "mlc.h"
#include "arena.h"

//struct nn* neunew(struct arena* arena) {
//	aalloc(arena, );
//}
//
struct layer* laynew(struct arena* arena, size_t weights, float (*activate)(float val)) {
	struct layer* l = aalloc(arena, sizeof(*l) + sizeof(float) * weights);
	if (!l)
		return NULL;
	l->weights = weights;
	l->bias = 0.1270;
	l->activate = activate;

	return l;
}

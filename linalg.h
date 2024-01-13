#ifndef LINALG_H
#define LINALG_H

#include "arena.h"

#include <stddef.h>
#include <stdbool.h>

struct matrix {
    size_t rows, cols;
    float** m;
};

/* Sets all values in m to zero */
void zeros(struct matrix* m);

/* creates a new zero-filled matrix, allocating from given arena */
struct matrix* matnew(struct arena*, size_t rows, size_t cols);

/* Performs a scalar product a 1D array
 *
 * Both arrays a and b must have the same size as the provided len, otherwise
 * it is UB.
 */
float dot(float a[], float b[], size_t len);

/* Performs matrix multiplication, passing the result in dst.
 *
 * The dst->rows _must_ be the same as a->rows, and dst->cols
 * must be the same as a->cols.
 * Returns true if successful, other false
 * */
bool matmul(struct matrix* dst, struct matrix* a, struct matrix* b);

#endif

#ifndef LINALG_H
#define LINALG_H

#include "arena.h"

#include <stddef.h>
#include <stdbool.h>

struct matrix {
	size_t rows, cols;
	float* m[/* rows */];
};

/* Sets all values in m to a random value, and return the given matrix */
struct matrix* matrand(struct matrix* M);

/* Sets all values in m to zero, and return the given matrix */
struct matrix* zeros(struct matrix* M);

/* creates a new uninitialized matrix, allocating from given arena */
struct matrix* matnew(struct arena* arena, size_t rows, size_t cols);

/* Set values of matrix to given arr*/
struct matrix* fromarr(struct matrix* M, const int cols, const float arr[][cols]);

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
bool matmul(struct matrix* dst, struct matrix* A, struct matrix* B);

#endif

#include "linalg.h"
#include "arena.h"

#include <assert.h>
#include <stdlib.h>

struct matrix* fromarr(struct matrix* M, const int cols, const float arr[][cols]) {
	if (!M)
		return NULL;

	for(size_t i = 0; i < M->rows; i++) {
		for (size_t j = 0; j < M->cols; j++) {
			M->m[i][j] = arr[i][j];
		}
	}
	return M;
}

struct matrix* matrand(struct matrix* M) {
	if (!M)
		return NULL;

	for (size_t i = 0; i < M->rows; i++) {
		for (size_t j = 0; j < M->cols; j++) {
			M->m[i][j] = (float)((double)rand() / RAND_MAX);
		}
	}
	return M;
}

struct matrix* zeros(struct matrix *M) 
{
	if (!M)
		return NULL;

	for (size_t i = 0; i < M->rows; i++) {
		for (size_t j = 0; i < M->cols; i++) {
			M->m[i][j] = 0;
		}
	}
	return M;
}

struct matrix* matnew(struct arena* arena, size_t rows, size_t cols) 
{
	if (!arena)
		return NULL;

	struct matrix* mat = aalloc(arena, sizeof(*mat) + sizeof(float *) * rows);
	if (mat == NULL) {
		return NULL;
	}
	mat->rows = rows;
	mat->cols = cols;
	for (size_t i = 0; i < rows; i++) {
		mat->m[i] = aalloc(arena, sizeof(mat->m[0]) * cols);
	}

	return mat;
}

float dot(float a[], float b[], size_t len) 
{
	float r = 0;
	for (size_t i = 0; i < len; i++) {
		r += (a[i] * b[i]);
    	}
	return r;
}

/* Private routine used for dot product in matmul*/
static float dotm(float a[], struct matrix* B, size_t length, size_t col) {
	assert(B->rows == length);

	float dot = 0;
	for (size_t i = 0; i < length; i++) {
		dot += a[i] * (B->m[i][col]);
	}
	return dot;
}

bool matmul(struct matrix* dst, struct matrix* A, struct matrix* B) 
{
	if (A->cols != B->rows   || 
	    dst->rows != A->rows || 
	    dst->cols != B->cols) {
		return false;
	}
	for (size_t i = 0; i < A->rows; i++) {
		for (size_t j = 0; j < B->cols; j++) {
			dst->m[i][j] = dotm(A->m[i], B, A->cols, j);
		}
	}


	return true;
}

#include "linalg.h"
#include "arena.h"

#include <assert.h>

struct matrix* fromarr(struct matrix* mat, const int cols, const float arr[][cols]) {
	if (!mat)
		return NULL;

	for(size_t i = 0; i < mat->rows; i++) {
		for (size_t j = 0; j < mat->cols; j++) {
			mat->m[i][j] = arr[i][j];
		}
	}
	return mat;
}

struct matrix* zeros(struct matrix *mat) 
{
	if (!mat)
		return NULL;

	for (size_t i = 0; i < mat->rows; i++) {
		for (size_t j = 0; i < mat->cols; i++) {
			mat->m[i][j] = 0;
		}
	}
	return mat;
}

struct matrix* matnew(struct arena* a, size_t rows, size_t cols) 
{
	if (!a)
		return NULL;

	struct matrix* mat = aalloc(a, sizeof(*a));
	if (mat == NULL) {
		return NULL;
	}
	mat->rows = rows;
	mat->cols = cols;
	mat->m = aalloc(a, sizeof(mat->m) * rows);
	for (size_t i = 0; i < rows; i++) {
		mat->m[i] = aalloc(a, sizeof(mat->m[0]) * cols);
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
static float dotm(float a[], struct matrix* b, size_t length, size_t col) {
	assert(b->rows == length);

	float dot = 0;
	for (size_t i = 0; i < length; i++) {
		dot += a[i] * (b->m[i][col]);
	}
	return dot;
}

bool matmul(struct matrix* dst, struct matrix* a, struct matrix* b) 
{
	if (a->cols != b->rows   || 
	    dst->rows != a->rows || 
	    dst->cols != b->cols) {
		return false;
	}
	for (size_t i = 0; i < a->rows; i++) {
		for (size_t j = 0; j < b->cols; j++) {
			dst->m[i][j] = dotm(a->m[i], b, a->cols, j);
		}
	}


	return true;
}

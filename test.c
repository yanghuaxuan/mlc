#include "arena.h"
#include "linalg.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


int main(void) {
	{ /* Test dot product */
		float yes[] = {1,2,3};
		float no[] = {4,5,6};
		assert(dot(yes, no, 3) == 32.0f);
	}
	{ /* Test matrix product */
		struct arena* arena = anew();
		if (!arena)
			exit(1);

		const float a1[][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
		const float a2[][3] = {{3,2,0}, {1,5,12}, {7,2,7}};
		const float ans[][3] = {{26,18,45},{59,45,102},{92,72,159}};
		struct matrix* dst = zeros(matnew(arena, 3, 3));
		struct matrix* m1 = fromarr(matnew(arena, 3, 3), 3, a1);
		struct matrix* m2 = fromarr(matnew(arena, 3, 3), 3, a2);
		if (!dst || !m1 || !m2)
			exit(1);

		matmul(dst, m1, m2);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				assert(dst->m[i][j] == ans[i][j]);
			}
		}
		afree(arena);
	}
	{ /* Test matrix product 2 */
		struct arena* arena = anew();
		if (!arena)
			exit(1);
		const float a1[][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
		const float a2[][1] = {{1},{2},{3}};
		const float ans[][3] = {{14},{32},{50}};
		struct matrix* dst = zeros(matnew(arena, 3, 1));
		struct matrix* m1 = fromarr(matnew(arena, 3, 3), 3, a1);
		struct matrix* m2 = fromarr(matnew(arena, 3, 1), 1, a2);
		if (!dst || !m1 || !m2)
			exit(1);
		matmul(dst, m1, m2);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 1; j++) {
				if (dst->m[i][j] != ans[i][j]) {
					printf("Expected: %f; Got: %f\n", ans[i][j], dst->m[i][j]);
					exit(1);
				}
			}
		}
		afree(arena);
	}
}

/**
 * @file hac_vec_filter_test.c
 * Tests:
 *  _hac_vec_collection.h:
 *   HAC_VEC_FILTER()
 * Finds all pythagorean triples with a perimeter of 1000 using HAC_VEC_FILTER() and prints the first one.
 */
#include <stdio.h>
#include "hac_vec.h"

typedef struct{int a, b, c;} Triangle;

int isPythag(Triangle t){
	return t.a*t.a + t.b*t.b == t.c*t.c;
}

int main(void){
	HAC_VEC_T_NEW(Triangle);
	HAC_VEC_T(Triangle) triangles = HAC_VEC_EMPTY(Triangle);
	for(int c = 5; 2*c < 1000; ++c){
		for(int a = 2; a < c - 1 && 2*a + c < 1000; ++a){
			HAC_VEC_PUSHR(Triangle, &triangles, ((Triangle){a, 1000 - a - c, c}));
		}
	}
	HAC_VEC_T(Triangle) rights =
	HAC_VEC_FILTER(Triangle, &triangles, isPythag(e));
	HAC_VEC_DELETE(Triangle, &triangles);
	Triangle right = HAC_VEC_GET(Triangle, &rights, 0);
	printf("%i, %i, %i: %i\n", right.a, right.b, right.c, right.a*right.b*right.c);
	HAC_VEC_DELETE(Triangle, &rights);
}


/**
 * @file hac_seq_filter_test.c
 * Tests:
 *  _hac_seq_collection.h:
 *   HAC_SEQ_FILTER()
 * Finds all pythagorean triples with a perimeter of 1000 using HAC_SEQ_FILTER() and prints the first one.
 */
#include <stdio.h>
#include "hac_seq.h"

typedef struct{int a, b, c;} Triangle;

int isPythag(Triangle t){
	return t.a*t.a + t.b*t.b == t.c*t.c;
}

int main(void){
	HAC_SEQ_T_NEW(Triangle);
	HAC_SEQ_T(Triangle) triangles = HAC_SEQ_EMPTY(Triangle);
	for(int c = 5; 2*c < 1000; ++c){
		for(int a = 2; a < c - 1 && 2*a + c < 1000; ++a){
			HAC_SEQ_PUSHR(Triangle, &triangles, ((Triangle){a, 1000 - a - c, c}));
		}
	}
	HAC_SEQ_T(Triangle) rights =
	HAC_SEQ_FILTER(Triangle, &triangles, isPythag(e));
	HAC_SEQ_DELETE(Triangle, &triangles);
	Triangle right = rights.a->v;
	printf("%i, %i, %i: %i\n", right.a, right.b, right.c, right.a*right.b*right.c);
	HAC_SEQ_DELETE(Triangle, &rights);
}


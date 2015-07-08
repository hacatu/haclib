/**
 * @file hac_vec_sort_test.c
 * Tests:
 *  _hac_vec_access.h:
 *   HAC_VEC_SHUFFLE()
 *  _hac_vec_sortable.h:
 *   HAC_VEC_SORT()
 * Creates a vector, shuffles it, then sorts it.
 */
#include <stdio.h>
#include <time.h>
#include "hac_vec.h"

int rand_interval(int min, int max){
	int r;
	int range = max - min + 1;
	int buckets = RAND_MAX/range;
	int limit = buckets*range;
	do{
		r = rand();
	}while(r >= limit);
	return min + (r/buckets);
}

int comp(int a, int b){
	if(a < b){
		return -1;
	}else if(a > b){
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[]){
	if(argc != 2){
		puts("Call this test with a random seed as the only argument.");
		return 1;
	}
	HAC_VEC_T_NEW(int);
	srand(atoll(argv[1]));
	HAC_VEC_T(int) vec = HAC_VEC_RANGE(int, 1, 100, 1);
	HAC_VEC_SHUFFLE(int, &vec, HAC_VEC_SWAP(int, v, i, j), rand_interval(m, n));
	HAC_VEC_SORT(int, &vec, comp(e1, e2), HAC_VEC_SWAP(int, v, i, j));
	puts("Sorted:");
	HAC_VEC_FOREACH(int, &vec, printf("%i,", e));
	puts("");
	HAC_VEC_DELETE(int, &vec);
}


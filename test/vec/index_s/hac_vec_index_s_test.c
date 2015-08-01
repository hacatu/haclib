/**
 * @file hac_vec_sort_test.c
 * Tests:
 *  _hac_vec_sortable.h:
 *   HAC_VEC_INDEX_S()
 */
#include <stdio.h>
#include "hac_vec.h"

int comp(int a, int b){
	if(a < b){
		return -1;
	}else if(a > b){
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[]){
	HAC_VEC_T_NEW(int);
	HAC_VEC_T(int) vec = HAC_VEC_LIST(int, 0, 1, 2, 3, 4, 5);
	printf("%i\n", HAC_VEC_INDEX_S(int, &vec, 0, comp(e1, e2)));
	printf("%i\n", HAC_VEC_INDEX_S(int, &vec, 3, comp(e1, e2)));
	printf("%i\n", HAC_VEC_INDEX_S(int, &vec, 5, comp(e1, e2)));
	printf("%i\n", HAC_VEC_INDEX_S(int, &vec, -1, comp(e1, e2)));
	printf("%i\n", HAC_VEC_INDEX_S(int, &vec, 6, comp(e1, e2)));
	HAC_VEC_DELETE(int, &vec);
	vec = HAC_VEC_EMPTY(int);
	printf("%i\n", HAC_VEC_INDEX_S(int, &vec, 0, comp(e1, e2)));
}


/**
 * @file hac_vec_foreach_test.c
 * Tests:
 * 	_hac_it_forward.h:
 *   HAC_IT_V(),
 *  _hac_it_random_access.h:
 *   HAC_IT_GET(), HAC_IT_NEXT_BY(), HAC_IT_PREV_BY()
 *  _hac_vec_it.h:
 */
#include <stdio.h>
#include "hac_vec.h"
#include "hac_it.h"

HAC_VEC_T_NEW(int);
HAC_VEC_IT_INIT(int);

int main(void){
	HAC_VEC_T(int) vec = HAC_VEC_RANGE(int, 1, 100, 1);
	HAC_VEC_IT_T(int) it = HAC_VEC_IT(int, &vec);
	printf("%i\n", HAC_IT_V(&it));
	printf("%i\n", HAC_IT_GET(&it, 30));
	printf("%i\n", HAC_IT_NEXT_BY(&it, 25));
	printf("%i\n", HAC_IT_PREV_BY(&it, 16));
	HAC_VEC_DELETE(int, &vec);
}


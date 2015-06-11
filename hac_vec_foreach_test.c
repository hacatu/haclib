/**
 * @file hac_vec_foreach_test.c
 * Tests:
 * 	hac_vec.h:
 *   HAC_VEC_T_NEW(), HAC_VEC_T(), HAC_VEC_LEN(), HAC_VEC_FOREACH(), HAC_VEC_PUSHR()
 *  _hac_vec_base.h:
 *   HAC_VEC_DELETE(), HAC_VEC_FROM()
 *  _hac_vec_monoid.h:
 *   HAC_VEC_ALL()
 * Finds all prime numbers under 100 using a vector.
 */
#include <stdio.h>
#include "hac_vec.h"

int main(void){
	HAC_VEC_T_NEW(int);
	HAC_VEC_T(int) vec = HAC_VEC_FROM(int, 1, &(int[1]){2});
	for(int i = 2; i < 100; ++i){
		if(HAC_VEC_ALL(int, &vec, i%e)){
			HAC_VEC_PUSHR(int, &vec, i);
		}
	}
	printf("%i primes:\n", (int)HAC_VEC_LEN(int, &vec));
	HAC_VEC_FOREACH(int, &vec, printf("%i\n", e));
	HAC_VEC_DELETE(int, &vec);
}


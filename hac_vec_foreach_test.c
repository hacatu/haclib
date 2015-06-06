//hac_vec_foreach_test.c
#include <stdio.h>
#include "hac_vec.h"

/* Tests:
 * Pre:
 *  T_NEW, T, LEN, FOREACH, PUSHR
 * Base:
 *  DELETE, FROM
 * Monoid:
 *  ALL
 */

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


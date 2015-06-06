//hac_vec_foldl_test.v
#include <stdio.h>
#include "hac_vec.h"

/* Tests:
 * Reverse:
 *  Foldl
 */

int main(void){
	HAC_VEC_T_NEW(int);
	HAC_VEC_T(int) vec = HAC_VEC_RANGE(int, 1, 10, 1);
	HAC_VEC_T(int) reversed = HAC_VEC_NEW(int, 10);
	HAC_VEC_FOLDL(int, &vec, &reversed, ({HAC_VEC_PUSHR(int, l, e); l;}));
	HAC_VEC_DELETE(int, &vec);
	HAC_VEC_FOREACH(int, &reversed, printf("%i, ", e));
	puts("");
	HAC_VEC_DELETE(int, &reversed);
}


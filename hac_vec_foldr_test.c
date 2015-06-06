//hac_vec_foldr_test.c
#include <stdio.h>
#include "hac_vec.h"

/* Tests:
 * Forward:
 *  Range, Foldr
 */

int gcd(int a, int b){
	if(a > b){
		return gcd(b, a);
	}
	while(1){
		b %= a;
		if(!b){
			return a;
		}
		a %= b;
		if(!a){
			return b;
		}
	}
}

int lcm(int a, int b){
	return a*b/gcd(a, b);
}

int main(void){
	HAC_VEC_T_NEW(int);
	HAC_VEC_T(int) vec = HAC_VEC_RANGE(int, 1, 10, 1);
	int vec_lcm = HAC_VEC_FOLDR(int, &vec, 1, lcm(l, e));
	printf("%i\n", vec_lcm);
	HAC_VEC_DELETE(int, &vec);
}


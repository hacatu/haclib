/**
 * @file hac_vec_foldr_test.c
 * Tests:
 * 	_hac_vec_forward.h:
 *   HAC_VEC_RANGE(), HAC_VEC_FOLDR()
 * Finds the gcd of all numbers from 1 to 10 using HAC_VEC_FOLDR()
 */
#include <stdio.h>
#include "hac_vec.h"

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


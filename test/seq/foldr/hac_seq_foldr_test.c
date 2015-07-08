/**
 * @file hac_seq_foldr_test.c
 * Tests:
 * 	_hac_seq_forward.h:
 *   HAC_SEQ_RANGE(), HAC_SEQ_FOLDR()
 * Finds the gcd of all numbers from 1 to 10 using HAC_SEQ_FOLDR()
 */
#include <stdio.h>
#include "hac_seq.h"

int gcd(int a, int b){
	if(a > b){
		return gcd(b, a);
	}
	if(!a){
		return b;
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
	HAC_SEQ_T_NEW(int);
	HAC_SEQ_T(int) seq = HAC_SEQ_RANGE(int, 1, 10, 1);
	int seq_lcm = HAC_SEQ_FOLDR(int, &seq, 1, lcm(l, e));
	printf("%i\n", seq_lcm);
	HAC_SEQ_DELETE(int, &seq);
}


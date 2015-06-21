/**
 * @file hac_seq_foldr_test.c
 * Tests:
 * 	_hac_seq_forward.h:
 *   HAC_SEQ_RANGE(), HAC_SEQ_FOLDR()
 * Finds the gcd of all numbers from 1 to 10 using HAC_SEQ_FOLDR()
 */
#include <stdio.h>
#include "hac_seq.h"

/*
#undef __HAC_SEQ_T
#undef HAC_SEQ_T
#undef __HAC_SEQ_NODE_S
#undef __HAC_SEQ_NODE_T
#undef HAC_SEQ_T_NEW
#undef HAC_SEQ_EMPTY
#undef __HAC_SEQ_NEW
#undef HAC_SEQ_NEW
#undef __HAC_SEQ_PUSHR_NN
//#undef HAC_SEQ_PUSHR
#undef HAC_SEQ_DELETE
#undef HAC_SEQ_COPY
#undef HAC_SEQ_FROM
#undef HAC_SEQ_FOREACH
#undef HAC_SEQ_FOREACHP
#undef HAC_SEQ_MAP
#undef HAC_SEQ_IS_EMPTY
#undef __HAC_SEQ_MERGE
#undef HAC_SEQ_MERGE
#undef HAC_SEQ_COMBINE
#undef HAC_SEQ_ALL
#undef HAC_SEQ_ANY
#undef HAC_SEQ_CONTAINS
#undef HAC_SEQ_LEN
#undef HAC_SEQ_FILTER
//#undef HAC_SEQ_FOLDR
#undef HAC_SEQ_POPR
//#undef HAC_SEQ_RANGE
#undef HAC_SEQ_FOLDL
#undef HAC_SEQ_POPL
#undef HAC_SEQ_PUSHL
*/

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


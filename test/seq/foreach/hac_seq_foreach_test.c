/**
 * @file hac_seq_foreach_test.c
 * Tests:
 * 	hac_seq.h:
 *   HAC_SEQ_T_NEW(), HAC_SEQ_T(), HAC_SEQ_NEW(), HAC_SEQ_FOREACH(), HAC_SEQ_PUSHR()
 *  _hac_seq_base.h:
 *   HAC_SEQ_DELETE()
 *  _hac_seq_monoid.h:
 *   HAC_SEQ_LEN(), HAC_SEQ_ALL()
 * Finds all prime numbers under 100 using a sequence.
 */
#include <stdio.h>
#include "hac_seq.h"

int main(void){
	HAC_SEQ_T_NEW(int);
	HAC_SEQ_T(int) seq = HAC_SEQ_NEW(int, 2);
	for(int i = 2; i < 100; ++i){
		if(HAC_SEQ_ALL(int, &seq, i%e)){
			HAC_SEQ_PUSHR(int, &seq, i);
		}
	}
	printf("%i primes:\n", (int)HAC_SEQ_LEN(int, &seq));
	HAC_SEQ_FOREACH(int, &seq, printf("%i\n", e));
	HAC_SEQ_DELETE(int, &seq);
}


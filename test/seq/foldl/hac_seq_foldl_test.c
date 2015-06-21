/**
 * @file hac_seq_foldl_test.c
 * Tests:
 * 	_hac_seq_reverse.h:
 *   HAC_SEQ_FOLDL()
 * Reverses a sequence using HAC_SEQ_FOLDL()
 */
#include <stdio.h>
#include "hac_seq.h"

int main(void){
	HAC_SEQ_T_NEW(int);
	HAC_SEQ_T(int) seq = HAC_SEQ_RANGE(int, 1, 10, 1);
	HAC_SEQ_T(int) reversed = HAC_SEQ_EMPTY(int);
	HAC_SEQ_FOLDL(int, &seq, &reversed, ({HAC_SEQ_PUSHR(int, l, e); l;}));
	HAC_SEQ_DELETE(int, &seq);
	HAC_SEQ_FOREACH(int, &reversed, printf("%i, ", e));
	puts("");
	HAC_SEQ_DELETE(int, &reversed);
}


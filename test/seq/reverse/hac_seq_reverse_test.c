/**@file hac_seq_reverse_test.c
 * Tests:
 * Copies a sequence, deletes the original, and replaces the original with the copy reversed.
 */

#include <stdio.h>
#include "hac_seq.h"

int main(void){
	HAC_SEQ_T_NEW(int);
	HAC_SEQ_T(int) seq = HAC_SEQ_RANGE(int, 1, 10, 1);
	HAC_SEQ_T(int) other = HAC_SEQ_COPY(int, &seq);
	HAC_SEQ_DELETE(int, &seq);
	while(other.n){
		HAC_SEQ_PUSHL(int, &seq, HAC_SEQ_POPL(int, &other));
	}
	HAC_SEQ_FOREACH(int, &seq, printf("%i,", e));
	HAC_SEQ_DELETE(int, &seq);
	puts("");
}


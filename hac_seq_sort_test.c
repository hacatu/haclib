/**
 * @file hac_seq_sort_test.c
 * Tests:
 *  _hac_seq_shuffle.h:
 *   HAC_SEQ_SHUFFLE()
 *  _hac_seq_sortable.h:
 *   HAC_SEQ_SORT()
 * Creates a vector, shuffles it, then sorts it.
 */
#include <stdio.h>
#include <time.h>
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
#undef HAC_SEQ_PUSHR
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
#undef HAC_SEQ_FOLDR
#undef HAC_SEQ_POPR
#undef HAC_SEQ_RANGE
#undef HAC_SEQ_FOLDL
#undef HAC_SEQ_POPL
#undef HAC_SEQ_PUSHL
//#undef __HAC_SEQ_FIXP
//#undef __HAC_SEQ_SHUFFLE_MERGE
//#undef __HAC_SEQ_SHUFFLE_STEP
//#undef HAC_SEQ_SHUFFLE
//#undef __HAC_SEQ_MERGE_SORTED
//#undef __HAC_SEQ_MSTEP
//#undef __HAC_SEQ_MSORT
//#undef HAC_SEQ_SORT
*/

double rand_double(void){
	return (double)rand()/((double)RAND_MAX + 1.);
}

int comp(int a, int b){
	if(a < b){
		return -1;
	}else if(a > b){
		return 1;
	}
	return 0;
}

int main(void){
	HAC_SEQ_T_NEW(int);
	srand(time(NULL));
	HAC_SEQ_T(int) seq = HAC_SEQ_RANGE(int, 1, 10, 1);
	HAC_SEQ_SHUFFLE(int, &seq, rand_double());
	puts("Shuffled:");
	HAC_SEQ_FOREACH(int, &seq, printf("%i,", e));
	puts("");
	HAC_SEQ_DELETE(int, &seq);
}


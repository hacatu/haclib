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

int main(int argc, char *argv[]){
	if(argc != 2){
		puts("Call with the random seed as the only argument.");
		return 1;
	}
	HAC_SEQ_T_NEW(int);
	srand(atoll(argv[1]));
	HAC_SEQ_T(int) seq = HAC_SEQ_RANGE(int, 1, 10, 1);
	HAC_SEQ_SHUFFLE(int, &seq, rand_double());
	//puts("Shuffled:");
	//HAC_SEQ_FOREACH(int, &seq, printf("%i,", e));
	//puts("");
	HAC_SEQ_SORT(int, &seq, comp(e1, e2));
	printf("Sorted (%i):\n", (int)seq.n);
	HAC_SEQ_FOREACH(int, &seq, printf("%i,", e));
	puts("");
	HAC_SEQ_DELETE(int, &seq);
}


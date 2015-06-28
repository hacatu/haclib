/**
 * @file hac_avl_remove_test.c
 * Tests:
 *  _hac_avl_remove.h:
 *   HAC_AVL_REMOVE()
 * 
 */
#include <stdio.h>
#include "hac_avl.h"
#include "hac_avl/_hac_avl_check.h"

int compInts(int e1, int e2){
	if(e1 < e2){
		return -1;
	}else if(e1 > e2){
		return 1;
	}else{
		return 0;
	}
}

int main(void){
	HAC_AVL_T_NEW(int);
	HAC_AVL_T(int) tree = HAC_AVL_EMPTY(int);
	int es[10], i, e, t;
	for(i = 0; i < 10; ++i){
		e = rand();
		es[i] = e;
		printf("inserting %i\n", e);
		HAC_AVL_INSERT(int, &tree, e, compInts(e1, e2));
	}
	printf("root: %i\n", tree.r->v);
	while(i){
		e = rand()%i;
		t = es[e];
		es[e] = es[i - 1];
		es[i - 1] = t;
		__HAC_AVL_PRINT(int, tree.r);
		printf("\nremoving %i\n", t);
		HAC_AVL_REMOVE(int, &tree, t, compInts(e1, e2));
		if(!__HAC_AVL_CHECK(int, &tree)){
			abort();
		}
		if(!__HAC_AVL_CHECK_AVL(tree.r, sizeof(__HAC_AVL_NODE_T(int)))){
			puts("CHECK_AVL failed");
			abort();
		}
		--i;
	}
}


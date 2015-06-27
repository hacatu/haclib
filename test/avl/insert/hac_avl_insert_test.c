/**
 * @file hac_avl_insert_test.c
 * Tests:
 *  hac_avl.h:
 *   HAC_VEC_T_NEW(), HAC_VEC_T(), HAC_AVL_EMPTY()
 *  _hac_avl_insert.h:
 *   HAC_AVL_INSERT()
 *  _hac_avl_base.h:
 *   HAC_AVL_DELETE()
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
	for(int i = 0, e; i < 10; ++i){
		e = rand();
		printf("inserting %i\n", e);
		HAC_AVL_INSERT(int, &tree, e, compInts(e1, e2));
		if(!__HAC_AVL_CHECK(int, &tree)){
			abort();
		}
		if(!__HAC_AVL_CHECK_AVL(tree.r, sizeof(__HAC_AVL_NODE_T(int)))){
			puts("CHECK_AVL failed");
			abort();
		}
		printf("root: %i\n", tree.r->v);
	}
	HAC_AVL_DELETE(int, &tree);
}


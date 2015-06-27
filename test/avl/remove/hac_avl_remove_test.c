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

#if 0
#undef __HAC_AVL_T
#undef HAC_AVL_T
#undef __HAC_AVL_NODE_S
#undef __HAC_AVL_NODE_T
#undef HAC_AVL_T_NEW
#undef HAC_AVL_EMPTY
#undef __HAC_AVL_NEW
#undef HAC_AVL_NEW
#undef __HAC_AVL_CLIMB
#undef __HAC_AVL_NEAREST
#undef HAC_AVL_NEAREST
#undef __HAC_AVL_GET
#undef HAC_AVL_GET
#undef __HAC_AVL_FIRST_POSTORDER
#undef __HAC_AVL_NEXT_POSTORDER
#undef __HAC_AVL_FIRST_PREORDER
#undef __HAC_AVL_NEXT_PREORDER
#undef __HAC_AVL_NEXT_PREORDER_WRAPPED
#undef __HAC_AVL_FIRST_INORDER
#undef __HAC_AVL_NEXT_INORDER
#undef __HAC_AVL_LAST_INORDER
#undef __HAC_AVL_PREV_INORDER
#undef __HAC_AVL_ROTATER
#undef __HAC_AVL_ROTATEL
#undef __HAC_AVL_INSERT_FIXK
#undef __HAC_AVL_INSERT_REBALANCE
#undef __HAC_AVL_INSERT
#undef HAC_AVL_INSERT
//#undef __HAC_AVL_REMOVE_TRUNK
//#undef __HAC_AVL_REMOVE_NODE
//#undef __HAC_AVL_REMOVE
//#undef HAC_AVL_REMOVE
#undef __HAC_AVL_DELETE
#undef HAC_AVL_DELETE
#undef HAC_AVL_COPY
#undef HAC_AVL_FROM
#endif

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


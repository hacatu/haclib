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
<<<<<<< HEAD
#include "hac_avl/_hac_avl_check.h"
=======

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
//#undef __HAC_AVL_ROTATER
//#undef __HAC_AVL_ROTATEL
//#undef __HAC_AVL_INSERT_FIXK
//#undef __HAC_AVL_INSERT_REBALANCE
//#undef __HAC_AVL_INSERT
//#undef HAC_AVL_INSERT
#undef __HAC_AVL_REMOVE_TRUNK
#undef __HAC_AVL_REMOVE_NODE
#undef __HAC_AVL_REMOVE
#undef HAC_AVL_REMOVE
#undef __HAC_AVL_DELETE
#undef HAC_AVL_DELETE
#undef HAC_AVL_COPY
#undef HAC_AVL_FROM
#endif
>>>>>>> e449e65b666b5be957b45a65357d77ff12dcdb10

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
<<<<<<< HEAD
		if(!__HAC_AVL_CHECK(int, &tree)){
			abort();
		}
		if(!__HAC_AVL_CHECK_AVL(tree.r, sizeof(__HAC_AVL_NODE_T(int)))){
			puts("CHECK_AVL failed");
			abort();
		}
		printf("root: %i\n", tree.r->v);
=======
>>>>>>> e449e65b666b5be957b45a65357d77ff12dcdb10
	}
	HAC_AVL_DELETE(int, &tree);
}


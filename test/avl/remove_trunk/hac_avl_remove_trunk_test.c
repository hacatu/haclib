/**
 * @file hac_avl_remove_trunk_test.c
 * Tests:
 *  _hac_avl_remove.h:
 *   HAC_AVL_REMOVE()
 * 
 */
#include <stdio.h>
#include "hac_avl.h"
#include "hac_avl/_hac_avl_check.h"

#if 0
#undef HAC_AVL_T_NEW
#undef __HAC_AVL_NODE_T
#undef __HAC_AVL_NODE_CHECK
#undef __HAC_AVL_GET
#undef __HAC_AVL_REMOVE_FIXK
#undef __HAC_AVL_REMOVE_BALANCE
#undef __HAC_AVL_REMOVE_REPLACE
#endif

#define free(a)

HAC_AVL_T_NEW(int);

size_t s[6] = {1, 2, 2, 2, 3, 3};

__HAC_AVL_NODE_T(int) r[6][3] = {
	{
		{1, 0,0x0000,0x0000,0x0000},
	},{
		{1,+1,r[1]+1,0x0000,0x0000},
		{2, 0,0x0000,0x0000,r[1]+0},
	},{
		{1,-1,0x0000,r[2]+1,0x0000},
		{2, 0,0x0000,0x0000,r[2]+0},
	},{
		{2,+1,r[3]+1,0x0000,0x0000},
		{1, 0,0x0000,0x0000,r[3]+0},
	},{
		{2,+2,r[4]+1,0x0000,0x0000},
		{1,+1,r[4]+2,0x0000,r[4]+0},
		{0, 0,0x0000,0x0000,r[4]+1},
	},{
		{3,+2,r[5]+1,0x0000,0x0000},
		{1,-1,0x0000,r[5]+2,r[5]+0},
		{2, 0,0x0000,0x0000,r[5]+1},
	}
};

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
	__HAC_AVL_NODE_T(int) *n;
	for(size_t i = 0; i < 6; ++i){
		printf("Testing tree %i\n", (int)i);
		if(!__HAC_AVL_NODE_CHECK(int, r[i])){
			abort();
		}
		n = __HAC_AVL_GET(int, r[i], 1, compInts(e1, e2));
		printf("removing %i\n", n->v);
		n = __HAC_AVL_REMOVE_TRUNK(int, n);
		if(n){
			printf("new root %i\n", n->v);
		}else{
			puts("new root 0x0");
		}
		if(!__HAC_AVL_NODE_CHECK(int, n)){
			abort();
		}
	}
}


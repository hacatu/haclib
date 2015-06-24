/**
 * @file hac_avl_rotate_test.c
 * This is not how code using haclib should be written, but these things need to be tested without insertion/removal/deletion possibly getting in the way.
 * Tests:
 *  _hac_avl_rotation.h:
 *   __HAC_AVL_ROTATER()
 *   __HAC_AVL_ROTATEL()
 */
#include <stdio.h>
#include "hac_avl.h"

/* 5, 4, 3, 2, 1
 *     5       5       5
 *    /       /       /
 *   4       4       3
 *  /       /       / \
 * 2       3       2   4
 *  \     /         \
 *   3   2           1
 *  /     \
 * 1       1
 */

HAC_AVL_T_NEW(int);

void printOffset(void *base, void *memb, size_t s){
	if(memb){
		printf("n+%i", (memb - base)/s);
	}else{
		printf("0x0");
	}
}

void printIntAVLTreeArray(size_t n, __HAC_AVL_NODE_T(int) a[n]){
	puts("{");
	for(size_t i = 0; i < n; ++i){
		printf("    {%i,%+i,", a[i].v, a[i].k);
		printOffset(a, a[i].a, sizeof(__HAC_AVL_NODE_T(int)));
		printf(",");
		printOffset(a, a[i].b, sizeof(__HAC_AVL_NODE_T(int)));
		printf(",");
		printOffset(a, a[i].p, sizeof(__HAC_AVL_NODE_T(int)));
		printf("},\n");
	}
	puts("}");
}

int main(void){
	__HAC_AVL_NODE_T(int) n[5] =
	{/*This is so hacky I cried.*/
	  /*{v, k,  a,  b,  p},*/
		{5,+4,n+1,0x0,0x0},
		{4,+3,n+3,0x0,n+0},
		{3,+1,n+4,0x0,n+3},
		{2,-2,0x0,n+2,n+1},
		{1, 0,0x0,0x0,n+2},
	};
	printIntAVLTreeArray(5, n);
	__HAC_AVL_ROTATEL(int, n->a->a);
	printIntAVLTreeArray(5, n);
	__HAC_AVL_ROTATER(int, n->a);
	printIntAVLTreeArray(5, n);
}


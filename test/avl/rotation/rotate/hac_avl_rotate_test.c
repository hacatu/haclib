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
#include "hac_avl/_hac_avl_check.h"

/* 6, 5, 4, 3, 2, 1, 0
 *       6         6       6
 *      /         /       /
 *     4         4       3
 *    / \       / \     / \
 *   1   5     3   5   1   4
 *  / \       /       / \   \
 * 0   3     1       0   2   5
 *    /     / \
 *   2     0   2
 */

HAC_AVL_T_NEW(int);

void printOffset(void *base, void *memb, size_t s){
	if(memb){
		printf("n+%i", (int)((memb - base)/s));
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
	__HAC_AVL_NODE_T(int) n[7] =
	{/*This is so hacky I cried.*/
	  /*{v, k,  a,  b,  p},*/
		{0, 0,0x0,0x0,n+1},
		{1,-1,n+0,n+3,n+4},
		{2, 0,0x0,0x0,n+3},
		{3,+1,n+2,0x0,n+1},
		{4,+2,n+1,n+5,n+6},
		{5, 0,0x0,0x0,n+4},
		{6,+4,n+4,0x0,0x0},
	}, *a = n + 6;
	printIntAVLTreeArray(7, n);
	if(!__HAC_AVL_NODE_CHECK(int, a)){abort();}
	__HAC_AVL_ROTATEL(int, a->a->a);
	printIntAVLTreeArray(7, n);
	if(!__HAC_AVL_NODE_CHECK(int, a)){abort();}
	__HAC_AVL_ROTATER(int, a->a);
	printIntAVLTreeArray(7, n);
	if(!__HAC_AVL_NODE_CHECK(int, a)){abort();}
}


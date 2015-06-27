/**
 * @file hac_avl_preorder_test.c
 * This is not how code using haclib should be written, but these things need to be tested without insertion/removal/deletion possibly getting in the way.
 * Tests:
 *  _hac_avl___traversal.h:
 *   __HAC_AVL_FIRST_PREORDER()
 *   __HAC_AVL_NEXT_PREORDER()
 */
#include <stdio.h>
#include "hac_avl.h"

/* 72, 65, 23, 73, 29, 97, 08, 36, 66, 74
 *  0,  1,  2,  3,  4,  5,  6,  7,  8,  9
 *         72
 *        /  \
 *       /    \
 *      65    73
 *     /  \     \
 *    23  66    97
 *   /  \      /
 *  08  29    74
 *        \
 *        36
 */

HAC_AVL_T_NEW(int);

int main(void){
	__HAC_AVL_NODE_T(int) n[10] =
	{/*This is so hacky I cried.*/
	  /*{ v, k,  a,  b,  p},*/
		{72,+1,n+1,n+3,0x0},
		{65,+2,n+2,n+8,n+0},
		{23,-1,n+6,n+4,n+1},
		{73,-2,0x0,n+5,n+0},
		{29,-1,0x0,n+7,n+2},
		{97,+1,n+9,0x0,n+3},
		{ 8, 0,0x0,0x0,n+2},
		{36, 0,0x0,0x0,n+4},
		{66, 0,0x0,0x0,n+1},
		{74, 0,0x0,0x0,n+5},
	};
	for(__HAC_AVL_NODE_T(int) *it = __HAC_AVL_FIRST_PREORDER(int, n); it; it = __HAC_AVL_NEXT_PREORDER(int, it)){
		printf("%i,", it->v);
	}
	puts("");
}


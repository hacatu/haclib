/**
 * @file hac_avl_rotater_test.c
 * This is not how code using haclib should be written, but these things need to be tested without insertion/removal/deletion possibly getting in the way.
 * Tests:
 *  _hac_avl_rotation.h:
 *   __HAC_AVL_ROTATER()
 *   __HAC_AVL_ROTATEL()
 */
#include <stdio.h>
#include "hac_avl.h"

/* 5, 4, 3, 2, 1
 *     5
 *    /
 *   4
 *  /
 * 2
 *  \
 *   3
 *  /
 * 1
 */

int main(void){
	HAC_AVL_T_NEW(int);
	__HAC_AVL_NODE_T(int) n[5] =
	{/*This is so hacky I cried.*/
	  /*{v, k,  a,  b,  p},*/
		{5,+4,n+1,0x0,0x0},
		{4,+3,n+3,0x0,n+0},
		{3,+1,n+4,0x0,n+3},
		{2,-2,0x0,n+2,n+1},
		{1, 0,0x0,0x0,n+2},
	};
	
}


/**
 * @file hac_avl_new_test.c
 * Tests:
 *  hac_avl.h:
 *   HAC_VEC_T_NEW(), HAC_VEC_T(), HAC_AVL_NEW(), HAC_AVL_DELETE()
 */
#include <stdio.h>
#include "hac_avl.h"

int main(void){
	HAC_AVL_T_NEW(int);
	HAC_AVL_T(int) tree = HAC_AVL_NEW(int, 0);
	HAC_AVL_DELETE(int, &tree);
}


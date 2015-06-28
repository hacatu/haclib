/**@file _hac_avl___traversal.h*/
#include "_hac_avl___preorder.h"
#include "_hac_avl___inorder.h"
#include "_hac_avl___postorder.h"
#include "_HAC_AVL___breadthfirst.h"
#define /*void*/__HAC_AVL_PRINT(base_t, /*__HAC_AVL_NODE_T**/root) ({  \
	for(__HAC_AVL_NODE_T(base_t) *_it = __HAC_AVL_FIRST_INORDER(base_t, root); _it; _it = __HAC_AVL_NEXT_INORDER(base_t, _it)){\
		printf("%i,", _it->v);                                         \
	}                                                                  \
})//END __HAC_AVL_PRINT


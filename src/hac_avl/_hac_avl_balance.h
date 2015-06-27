/**@file _hac_avl_balance.h*/
#define /*void*/__HAC_AVL_INSERT_FIXK(base_t, /*__HAC_AVL_NODE_T**/n) __HAC_AVL_FIXK(base_t, n, 1)

#define /*void*/__HAC_AVL_REMOVE_FIXK(base_t, /*__HAC_AVL_NODE_T**/n) __HAC_AVL_FIXK(base_t, n, -1)

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_REBALANCE(base_t, /*__HAC_AVL_NODE_T**/n) ({\
	__HAC_AVL_NODE_T(base_t) *_n_ = n;                                 \
	while(n){                                                          \
		_n_ = n;                                                       \
		if(n->k == 2){                                                 \
			if(n->a->k == -1){                                         \
				__HAC_AVL_ROTATEL(base_t, n->a);                       \
			}                                                          \
			__HAC_AVL_ROTATER(base_t, n);                              \
		}else if(n->k == -2){                                          \
			if(n->b->k == 1){                                          \
				__HAC_AVL_ROTATER(base_t, n->b);                       \
			}                                                          \
			__HAC_AVL_ROTATEL(base_t, n);                              \
		}                                                              \
		n = n->p;                                                      \
	}                                                                  \
	_n_;                                                               \
})//END __HAC_AVL_REBALANCE


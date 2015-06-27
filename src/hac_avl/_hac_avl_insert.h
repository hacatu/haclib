/**@file _hac_avl_insert.h*/
#define __HAC_AVL_INSERT_BALANCE __HAC_AVL_REBALANCE

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_INSERT_UNBALANCED(base_t, /*__HAC_AVL_NODE_T**/root, /*base_t*/val, comp) ({\
	__HAC_AVL_NODE_T(base_t) *_n = __HAC_AVL_NEAREST(base_t, root, val, comp), *_v = NULL;\
	int _o = ({base_t e1 = val, e2 = _n->v; comp;});                   \
	if(_o){                                                            \
		_v = calloc(1, sizeof(__HAC_AVL_NODE_T(base_t)));              \
		if(_v){                                                        \
			_v->v = val;                                               \
			_v->p = _n;                                                \
			if(_o < 0){                                                \
				_n->a = _v;                                            \
			}else{                                                     \
				_n->b = _v;                                            \
			}                                                          \
			_n = _v;                                                   \
			__HAC_AVL_INSERT_FIXK(base_t, _n);                         \
		}                                                              \
	}                                                                  \
	_v;                                                                \
})//END __HAC_AVL_INSERT_UNBALANCED

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_INSERT(base_t, /*__HAC_AVL_NODE_T**/root, /*base_t*/val, comp) ({\
	__HAC_AVL_NODE_T(base_t) *_n = __HAC_AVL_INSERT_UNBALANCED(base_t, root, val, comp);\
	if(_n){                                                            \
		_n = __HAC_AVL_INSERT_BALANCE(base_t, _n);                     \
	}                                                                  \
	_n;                                                                \
})//END __HAC_AVL_INSERT

/**
 * @brief insert a value into an avl tree.
 * Automatically balances the tree.  You're welcome.
 * @param base_t the base type.
 * @param avl a pointer to the tree to insert into.
 * @param val the value to insert into the tree.
 * @param comp an expression containing e1 and e2 (the elements to compare).  Should evaluate < 0 if e1 < e2, > 0 if e1 > e2, and == 0 if e1 == e2.  Remember that just using - will sometimes cause overflow.
 * @return 1 if insertion succeeds, 0 if it fails (due to memory exhaustion or duplicate entries).
 */
#define HAC_AVL_INSERT(base_t, avl, val, comp) ({                      \
	int _ret = 0;                                                      \
	__HAC_AVL_NODE_T(base_t) *_n;                                      \
	HAC_AVL_T(base_t) *_avl = (avl);                                   \
	base_t _val = (val);                                               \
	if(!_avl->r){                                                      \
		*_avl = HAC_AVL_NEW(base_t, _val);                             \
		_ret = !!_avl->r;                                              \
	}else{                                                             \
		_n = __HAC_AVL_INSERT(base_t, _avl->r, _val, comp);            \
		if(_n){                                                        \
			_avl->r = _n;                                              \
			_ret = 1;                                                  \
		}                                                              \
	}                                                                  \
	_ret;                                                              \
})//END HAC_AVL_INSERT


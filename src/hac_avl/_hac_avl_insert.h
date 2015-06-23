/**@file _hac_avl_insert.h*/
#define /*void*/__HAC_AVL_INSERT_FIXK(base_t, /*__HAC_AVL_NODE_T**/n) ({\
	while(n->p){                                                       \
		if(n == n->p->a){                                              \
			++n->p->k;                                                 \
		}else{                                                         \
			--n->p->k;                                                 \
		}                                                              \
		n = n->p;                                                      \
	}                                                                  \
})//END __HAC_AVL_INSERT_FIXK

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_INSERT_REBALANCE(base_t, /*__HAC_AVL_NODE_T**/n) ({\
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
})//END __HAC_AVL_INSERT_REBALANCE

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_INSERT(base_t, /*__HAC_AVL_NODE_T**/root, /*base_t*/val, comp) ({\
	int _o;                                                            \
	__HAC_AVL_NODE_T(base_t) *_n = __HAC_AVL_NEAREST(base_t, root, val, comp), *_v;\
	base_t e1, e2;                                                     \
	_o = ({e1 = val; e2 = _n->v; comp;});                              \
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
			_n = _v;                                                   \
			_n = __HAC_AVL_INSERT_REBALANCE(base_t, _n);               \
		}else{                                                         \
			_n = NULL;                                                 \
		}                                                              \
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


/**@file _hac_avl___preorder.h*/
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_FIRST_PREORDER(base_t, /*__HAC_AVL_NODE_T**/root) (root)

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_NEXT_PREORDER(base_t, /*__HAC_AVL_NODE_T**/n) ({\
	__HAC_AVL_NODE_T(base_t) *_ret = (n);                              \
	if(_ret->a){                                                       \
		_ret = _ret->a;                                                \
	}else if(_ret->b){                                                 \
		_ret = _ret->b;                                                \
	}else{                                                             \
		while(_ret->p && _ret == _ret->p->b){                          \
			_ret = _ret->p;                                            \
		}                                                              \
		if(!_ret->p){                                                  \
			_ret = NULL;                                               \
		}else{                                                         \
			_ret = _ret->p->b;                                         \
		}                                                              \
	}                                                                  \
	_ret;                                                              \
})//END __HAC_AVL_NEXT_PREORDER

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_NEXT_PREORDER_WRAPPED(base_t, /*__HAC_AVL_NODE_T**/n, /*__HAC_AVL_NODE_T**/f) ({\
	__HAC_AVL_NODE_T(base_t) *_n = calloc(1, sizeof(__HAC_AVL_NODE_T(base_t)));\
	if(_n){                                                            \
		if(n->a){                                                      \
			n = n->a;                                                  \
			f->a = _n;                                                 \
		}else if(n->b){                                                \
			n = n->b;                                                  \
			f = f->b = _n;                                             \
		}else{                                                         \
			while(n->p && n == n->p->b){                               \
				n = n->p;                                              \
				f->p = _n;                                             \
			}                                                          \
			if(!n->p){                                                 \
				free(_n);                                              \
				_n = n = NULL;                                         \
			}else{                                                     \
				n = n->p->b;                                           \
				f->p->b = _n;                                          \
			}                                                          \
		}                                                              \
		if(_n){                                                        \
			_n->p = f;                                                 \
		}                                                              \
	}                                                                  \
	f = _n;                                                            \
})//END __HAC_AVL_NEXT_PREORDER_WRAPPED


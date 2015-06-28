/**@file _hac_avl_get.h*/
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_CLIMB(base_t, /*__HAC_AVL_NODE_T**/n) ({\
	if(n){                                                             \
		while(n->p){                                                   \
			n = n->p;                                                  \
		}                                                              \
	}                                                                  \
	n;                                                                 \
})//END __HAC_AVL_CLIMB

#define /*size_t*/__HAC_AVL_HEIGHT(base_t, /*__HAC_AVL_NODE_T**/n) ({  \
	__HAC_AVL_NODE_T(base_t) *_n_ = (n);                               \
	size_t _h = 0;                                                     \
	while(_n_){                                                        \
		_n_ = _n_->k >= 0 ? _n_->a : _n_->b;                           \
		++_h;                                                          \
	}                                                                  \
	_h;                                                                \
})//END __HAC_AVL_HEIGHT

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_NEAREST(base_t, /*__HAC_AVL_NODE_T**/root, /*base_t*/key, comp) ({\
	__HAC_AVL_NODE_T(base_t) *_n = root;                               \
	int _o;                                                            \
	base_t e1 = key, e2;                                               \
	while(1){                                                          \
		_o = ({e2 = _n->v; comp;});                                    \
		if(_o < 0){                                                    \
			if(_n->a){                                                 \
				_n = _n->a;                                            \
			}else{                                                     \
				break;                                                 \
			}                                                          \
		}else if(_o > 0){                                              \
			if(_n->b){                                                 \
				_n = _n->b;                                            \
			}else{                                                     \
				break;                                                 \
			}                                                          \
		}else{                                                         \
			break;                                                     \
		}                                                              \
	}                                                                  \
	_n;                                                                \
})//END __HAC_AVL_NEAREST

/**
 * @brief find the node with the nearest value to a key value in an avl tree.
 * @param base_t the base type.
 * @param avl a pointer to the tree to search.
 * @param key the value to look for in avl
 * @param comp an expression containing e1 and e2 (the elements to compare).  Should evaluate < 0 if e1 < e2, > 0 if e1 > e2, and == 0 if e1 == e2.  Remember that just using - will sometimes cause overflow.
 * @return a pointer to the nearest node.
 */
#define HAC_AVL_NEAREST(base_t, avl, key, comp) ({                     \
	__HAC_AVL_NODE_T(base_t) *_nearest = NULL;                         \
	HAC_AVL_T(base_t) *_avl = (avl);                                   \
	base_t _key = (key);                                               \
	if(_avl->r){                                                       \
		_nearest = __HAC_AVL_NEAREST(base_t, _avl->r, _key, comp);     \
	}                                                                  \
	_nearest;                                                          \
})//END HAC_AVL_NEAREST

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_GET(base_t, /*__HAC_AVL_NODE_T**/root, /*base_t*/key, comp) ({\
	__HAC_AVL_NODE_T(base_t) *_n = __HAC_AVL_NEAREST(base_t, root, key, comp);\
	if(_n && ({base_t e1 = _n->v, e2 = key; comp;})){                  \
		_n = NULL;                                                     \
	}                                                                  \
	_n;                                                                \
})//END __HAC_AVL_GET

/**
 * @brief get the node with the value equal to a key value in an avl tree.
 * @param base_t the base type.
 * @param avl a pointer to the tree to search.
 * @param key the value to look for in avl
 * @param comp an expression containing e1 and e2 (the elements to compare).  Should evaluate < 0 if e1 < e2, > 0 if e1 > e2, and == 0 if e1 == e2.  Remember that just using - will sometimes cause overflow.
 * @return a pointer to the matching node, or NULL if not found.
 */
#define HAC_AVL_GET(base_t, avl, key, comp) ({                         \
	__HAC_AVL_NODE_T(base_t) *_nearest = HAC_AVL_NEAREST(base_t, avl, key, comp);\
	if(_nearest && ({base_t e1 = _nearest->v, e2 = key; comp;})){      \
		_nearest = NULL;                                               \
	}                                                                  \
	_nearest;                                                          \
})//END HAC_AVL_GET


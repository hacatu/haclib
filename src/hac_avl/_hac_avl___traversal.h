/**@file _hac_avl___traversal.h*/
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_FIRST_POSTORDER(base_t, /*__HAC_AVL_NODE_T**/root) ({\
	__HAC_AVL_NODE_T(base_t) *_ret_ = (root);                          \
	while(1){                                                          \
		if(_ret_->a){                                                  \
			_ret_ = _ret_->a;                                          \
		}else if(_ret_->b){                                            \
			_ret_ = _ret_->b;                                          \
		}else{                                                         \
			break;                                                     \
		}                                                              \
	}                                                                  \
	_ret_;                                                             \
})//END __HAC_AVL_FIRST_POSTORDER

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_NEXT_POSTORDER(base_t, /*__HAC_AVL_NODE_T**/n) ({\
	__HAC_AVL_NODE_T(base_t) *_ret = (n);                              \
	if(!_ret->p){/*_ret is root.*/                                     \
		_ret = NULL;                                                   \
	}else if(_ret->p->a == _ret){/*_ret is the left child.*/           \
		if(_ret->p->b){                                                \
			_ret = __HAC_AVL_FIRST_POSTORDER(base_t, _ret->p->b);      \
		}else{                                                         \
			_ret = _ret->p;                                            \
		}                                                              \
	}else{                                                             \
		_ret = _ret->p;                                                \
	}                                                                  \
	_ret;                                                              \
})//END __HAC_AVL_NEXT_POSTORDER

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

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_FIRST_INORDER(base_t, /*__HAC_AVL_NODE_T**/root) ({\
	__HAC_AVL_NODE_T(base_t) *_ret_ = (root);                          \
	while(_ret_->a){                                                   \
		_ret_ = _ret_->a;                                              \
	}                                                                  \
	_ret_;                                                             \
})//END __HAC_AVL_FIRST_INORDER

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_NEXT_INORDER(base_t, /*__HAC_AVL_NODE_T**/n) ({\
	__HAC_AVL_NODE_T(base_t) *_ret = (n);                              \
	if(_ret->b){/*_ret has a right subtree, traverse it*/              \
		_ret = __HAC_AVL_FIRST_INORDER(base_t, _ret->b);               \
	}else{                                                             \
		while(1){/*walk up the tree*/                                  \
			if(!_ret->p){/*_ret is root*/                              \
				_ret = NULL;                                           \
				break;                                                 \
			}                                                          \
			if(_ret == _ret->p->a){/*_ret is the left child, visit parent*/\
				_ret = _ret->p;                                        \
				break;                                                 \
			}                                                          \
			_ret = _ret->p;                                            \
		}                                                              \
	}                                                                  \
	_ret;                                                              \
})//END __HAC_AVL_NEXT_INORDER

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_LAST_INORDER(base_t, /*__HAC_AVL_NODE_T**/root) ({\
	__HAC_AVL_NODE_T(base_t) *_ret_ = (root);                          \
	while(_ret_->b){                                                   \
		_ret_ = _ret_->b;                                              \
	}                                                                  \
	_ret_;                                                             \
})//END __HAC_AVL_FIRST_INORDER

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_PREV_INORDER(base_t, /*__HAC_AVL_NODE_T**/n) ({\
	__HAC_AVL_NODE_T(base_t) *_ret = (n);                              \
	if(_ret->a){/*_ret has a left subtree, traverse it*/               \
		_ret = __HAC_AVL_LAST_INORDER(base_t, _ret->a);                \
	}else{                                                             \
		while(1){/*walk up the tree*/                                  \
			if(!_ret->p){/*_ret is root*/                              \
				_ret = NULL;                                           \
				break;                                                 \
			}                                                          \
			if(_ret == _ret->p->b){/*_ret is the right child, visit parent*/\
				_ret = _ret->p;                                        \
				break;                                                 \
			}                                                          \
			_ret = _ret->p;                                            \
		}                                                              \
	}                                                                  \
	_ret;                                                              \
})//END __HAC_AVL_PREV_INORDER

#define /*void*/__HAC_AVL_PRINT(base_t, /*__HAC_AVL_NODE_T**/root) ({  \
	for(__HAC_AVL_NODE_T(base_t) *_it = __HAC_AVL_FIRST_INORDER(base_t, root); _it; _it = __HAC_AVL_NEXT_INORDER(base_t, _it)){\
		printf("%i,", _it->v);                                         \
	}                                                                  \
})//END __HAC_AVL_PRINT


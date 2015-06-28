/**@file _hac_avl___postorder.h*/
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


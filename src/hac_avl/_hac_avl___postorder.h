/**@file _hac_avl___postorder.h*/
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


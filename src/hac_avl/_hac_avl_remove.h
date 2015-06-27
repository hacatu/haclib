/**@file _hac_avl_remove.h*/
<<<<<<< HEAD
#define __HAC_AVL_REMOVE_BALANCE __HAC_AVL_REBALANCE

#define __HAC_AVL_REMOVE_REPLACE(node, replacement) ({                 \
	if(node->p){                                                       \
		if(node == node->p->a){                                        \
			node->p->a = replacement;                                  \
		}else{                                                         \
			node->p->b = replacement;                                  \
		}                                                              \
	}                                                                  \
})//END __HAC_AVL_REMOVE_REPLACE

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_REMOVE_TRUNK(base_t, /*__HAC_AVL_NODE_T**/node) ({\
	__HAC_AVL_NODE_T(base_t) *_node, *_t;                              \
	int _fixed = 0;                                                    \
	if(node->a){                                                       \
		_node = node->a;                                               \
		_node->p = node->p;                                            \
		__HAC_AVL_REMOVE_REPLACE(node, _node);                         \
	}else if(node->b){                                                 \
		_node = node->b;                                               \
		_node->p = node->p;                                            \
		__HAC_AVL_REMOVE_REPLACE(node, _node);                         \
	}else{                                                             \
		_node = node;                                                  \
		__HAC_AVL_REMOVE_FIXK(base_t, _node);                          \
		_node = node->p;                                               \
		_node = __HAC_AVL_REMOVE_BALANCE(base_t, _node);               \
		_fixed = 1;                                                    \
		__HAC_AVL_REMOVE_REPLACE(node, NULL);                          \
	}                                                                  \
	if(!_fixed){                                                       \
		_t = _node;                                                    \
		__HAC_AVL_REMOVE_FIXK(base_t, _t);                             \
		_node = __HAC_AVL_REMOVE_BALANCE(base_t, _node);               \
=======
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_REMOVE_TRUNK(base_t, /*__HAC_AVL_NODE_T**/node) ({\
	__HAC_AVL_NODE_T(base_t) *_node = node;                            \
	if(node->a){                                                       \
		node->a->p = node->p;                                          \
		if(node->p){                                                   \
			if(node == node->p->a){                                    \
				node->p->a = node->a;                                  \
			}else{                                                     \
				node->p->b = node->a;                                  \
			}                                                          \
		}                                                              \
		_node = node->a;                                               \
	}else if(node->b){                                                 \
		node->b->p = node->p;                                          \
		if(node->p){                                                   \
			if(node == node->p->a){                                    \
				node->p->a = node->b;                                  \
			}else{                                                     \
				node->p->b = node->b;                                  \
			}                                                          \
		}                                                              \
		_node = node->b;                                               \
	}else{                                                             \
		if(node->p){                                                   \
			if(node == node->p->a){                                    \
				node->p->a = NULL;                                     \
			}else{                                                     \
				node->p->b = NULL;                                     \
			}                                                          \
		}                                                              \
		_node = NULL;                                                  \
>>>>>>> e449e65b666b5be957b45a65357d77ff12dcdb10
	}                                                                  \
	free(node);                                                        \
	_node;                                                             \
})//END __HAC_AVL_REMOVE_TRUNK

<<<<<<< HEAD
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_REMOVE_NODE(base_t, /*__HAC_AVL_NODE_T**/node) ({\
	__HAC_AVL_NODE_T(base_t) *_z;                                      \
=======
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_REMOVE_NODE(base_t, /*__HAC_AVL_NODE_T**/root, /*__HAC_AVL_NODE_T**/node) ({\
	__HAC_AVL_NODE_T(base_t) *_z, *_root;                              \
>>>>>>> e449e65b666b5be957b45a65357d77ff12dcdb10
	if(!(node->a && node->b)){/*node does not have 2 children*/        \
		_z = node;                                                     \
	}else{                                                             \
		_z = __HAC_AVL_PREV_INORDER(base_t, node);                     \
		node->v = _z->v;                                               \
	}                                                                  \
<<<<<<< HEAD
	__HAC_AVL_REMOVE_TRUNK(base_t, _z);                                \
=======
	_root = __HAC_AVL_REMOVE_TRUNK(base_t, _z);                        \
	if(_z != root){                                                    \
		_root = root;                                                  \
	}                                                                  \
	_root;                                                             \
>>>>>>> e449e65b666b5be957b45a65357d77ff12dcdb10
})//END __HAC_AVL_REMOVE_NODE

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_REMOVE(base_t, /*__HAC_AVL_NODE_T**/root, /*base_t*/val, comp) ({\
	__HAC_AVL_NODE_T(base_t) *_n = __HAC_AVL_GET(base_t, root, val, comp);\
	if(_n){                                                            \
<<<<<<< HEAD
		_n = __HAC_AVL_REMOVE_NODE(base_t, _n);                        \
=======
		_n = __HAC_AVL_REMOVE_NODE(base_t, root, _n);                  \
>>>>>>> e449e65b666b5be957b45a65357d77ff12dcdb10
	}else{/*If val is not in the tree, return an unaligned pointer.*/  \
		_n = (__HAC_AVL_NODE_T(base_t)*)(char*)1;                      \
	}                                                                  \
	_n;                                                                \
})//END __HAC_AVL_REMOVE

/**
 * @brief remove a value from an avl tree.
 * Automatically balances the tree.  You're welcome.
 * @param base_t the base type.
 * @param avl a pointer to the tree to remove from.
 * @param val the value to remove from the tree.
 * @param comp an expression containing e1 and e2 (the elements to compare).  Should evaluate < 0 if e1 < e2, > 0 if e1 > e2, and == 0 if e1 == e2.  Remember that just using - will sometimes cause overflow.
 * @return 1 if removal succeeds, 0 if it fails (because the value to remove is already not in the tree).
 */
#define HAC_AVL_REMOVE(base_t, avl, val, comp) ({                      \
	int _ret = 0;                                                      \
	HAC_AVL_T(base_t) *_avl = (avl);                                   \
	__HAC_AVL_NODE_T(base_t) *_root;                                   \
	base_t _val = (val);                                               \
	if(_avl->r){                                                       \
		_root = __HAC_AVL_REMOVE(base_t, _avl->r, _val, comp);         \
		_ret = !((size_t)_root%sizeof(__HAC_AVL_NODE_T(base_t)));/*_root%size is 0 if _root is aligned to size.*/\
		if(_ret){/*_root is aligned*/                                  \
			_avl->r = _root;                                           \
		}                                                              \
	}                                                                  \
	_ret;                                                              \
})//END HAC_AVL_REMOVE


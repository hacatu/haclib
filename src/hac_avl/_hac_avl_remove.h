/**@file _hac_avl_remove.h*/
#define __HAC_AVL_REMOVE_TRUNK(base_t, node) ({                        \
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
		node = node->a;                                                \
	}else if(node->b){                                                 \
		node->b->p = node->p;                                          \
		if(node->p){                                                   \
			if(node == node->p->a){                                    \
				node->p->a = node->b;                                  \
			}else{                                                     \
				node->p->b = node->b;                                  \
			}                                                          \
		}                                                              \
		node = node->b;                                                \
	}else{                                                             \
		node = NULL;                                                   \
	}                                                                  \
	free(_node);                                                       \
	node;                                                              \
})//END __HAC_AVL_REMOVE_TRUNK

#define /*void*/__HAC_AVL_REMOVE_NODE(base_t, /*__HAC_AVL_NODE_T**/node) ({\
	__HAC_AVL_NODE_T(base_t) *_z;                                      \
	if(!(node->a && node->b)){/*node does not have 2 children*/        \
		_z = node;                                                     \
	}else{                                                             \
		_z = __HAC_AVL_PREV_INORDER(base_t, node);                     \
		node->v = _z->v;                                               \
	}                                                                  \
	__HAC_AVL_REMOVE_TRUNK(base_t, _z);                                \
})//END __HAC_AVL_REMOVE_NODE

#define /*int*/__HAC_AVL_REMOVE(base_t, /*__HAC_AVL_NODE_T**/root, /*base_t*/val, comp) ({\
	int _ret = 0, _o;                                                  \
	__HAC_AVL_NODE_T(base_t) *_n = __HAC_AVL_GET(base_t, root, val, comp);\
	if(_n){                                                            \
		_ret = (_n->p) ? 1 : 2;/*if _n is the root, return 2 so the tree can have its root pointer nulled.*/\
		__HAC_AVL_REMOVE_NODE(base_t, root, _n);                       \
	}                                                                  \
	_ret;                                                              \
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
	base_t _val = (val);                                               \
	if(!_avl->r){                                                      \
		_ret = 0;                                                      \
	}else{                                                             \
		_ret = __HAC_AVL_REMOVE(base_t, _avl->r, _val, comp);          \
		if(_ret == 2){/*_ret of 2 indicates root was removed and tree is empty*/\
			_avl->r = NULL;                                            \
		}                                                              \
	}                                                                  \
	!!_ret;                                                            \
})//END HAC_AVL_REMOVE


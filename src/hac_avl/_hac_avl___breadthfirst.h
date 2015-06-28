/**@file _hac_avl___breadthfirst.h*/
/* One advantage of breadth first traversal is it can cope with infinite trees.  This implementation cannot as it relies on
 * finding the height of a subtree, which requires finding the bottom.  However, infinite trees are also obviously impossible,
 * at least as data structures in memory.  In fact, the maximum height for a tree with 2^n elements is about 1.44n, and
 * the expected height from the bottom for a node aprroaches 2 as the number of elements grows.  Infinite trees could arise,
 * however, in game decision trees or similar, but those couldn't be implemented as avl trees, much as oaks are not maples.
 * This implementation does not use queues (which could be made using HAC_SEQ) to eliminate extra dependencies.
 */
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_FIRST_BREADTHFIRST(base_t, /*__HAC_AVL_NODE_T**/n) (n)

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_FIRST_BREADTHFIRST_D(base_t, /*__HAC_AVL_NODE_T**/n, /*size_t*/h, /*size_t*/dh) ({
	
})

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_NEXT_BREADTHFIRST(base_t, /*__HAC_AVL_NODE_T**/n) ({\
	__HAC_AVL_NODE_T(base_t) *_n = (n);                                \
	size_t _dh = 0, _h = __HAC_AVL_HEIGHT(base_t, _n);                 \
	if(_n->p){                                                         \
		do{                                                            \
			if(_n == _n->p->a && _h - _n->p->k >= _dh){                \
				_n = _n->p->b;                                         \
				_h -= _n->p->k;                                        \
				_n = __HAC_AVL_FIRST_BREADTHFIRST_D(base_t, _n, _h, _dh);\
				break;                                                 \
			}                                                          \
			_n = _n->p;                                                \
			_h += HAC_ABS(_n->k) + 1;                                  \
			++_dh;                                                     \
		}while(_n->p);                                                 \
		if(_dh){                                                       \
			++_dh;                                                     \
		}                                                              \
	}else{                                                             \
		++_dh;                                                         \
	}                                                                  \
	if(_dh){                                                           \
		if(_h < _dh){                                                  \
			_n = NULL;                                                 \
		}else{                                                         \
			_n = __HAC_AVL_FIRST_BREADTHFIRST_D(base_t, _n, _h, _dh);  \
		}                                                              \
	}                                                                  \
	_n;                                                                \
})//END __HAC_AVL_NEXT_BREADTHFIRST


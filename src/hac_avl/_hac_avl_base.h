/**@file _hac_avl_base.h*/
#define __HAC_AVL_DELETE(base_t, avl) ({                               \
	__HAC_AVL_NODE_T(base_t) *_cur = __HAC_AVL_FIRST_POSTORDER(base_t, avl->r), *_next;\
	while(_cur){                                                       \
		_next = __HAC_AVL_NEXT_POSTORDER(base_t, _cur);                \
		free(_cur);                                                    \
		_cur = _next;                                                  \
	}                                                                  \
	*_avl = HAC_AVL_EMPTY(base_t);                                     \
	returnvoid;                                                        \
})//END __HAC_AVL_DELETE

/**
 * @brief Deletes an avl tree.
 * Frees all nodes and sets the header to empty, but does not delete the values in any way, so HAC_AVL_FOREACH(base_t, avl, expr) may be needed.
 * @param base_t the base type.
 * @param avl a pointer to the avl tree to delete.
 */
#define HAC_AVL_DELETE(base_t, avl) ({                                 \
	HAC_AVL_T(base_t) *_avl = (avl);                                   \
	__HAC_AVL_DELETE(base_t, _avl);                                    \
})//END HAC_AVL_DELETE

/**
 * @brief Copies an avl tree.
 * Does not deep copy the values in any way.
 * @param base_t the base type.
 * @param avl a pointer to the avl tree.
 * @return a new avl tree that is a copy of avl.
 */
#define HAC_AVL_COPY(base_t, avl) ({                                   \
	HAC_AVL_T(base_t) *_avl = (avl), _ret;                             \
	__HAC_AVL_NODE_T(base_t) *n = _avl->r, *f = calloc(1, sizeof(__HAC_AVL_NODE_T(base_t)));\
	_ret = (HAC_AVL_T(base_t)){.r = f};                                \
	while(f){                                                          \
		f->v = n->v;                                                   \
		f->k = n->k;                                                   \
		__HAC_AVL_NEXT_PREORDER_WRAPPED(base_t, n, f);                 \
	}                                                                  \
	if(n){                                                             \
		__HAC_AVL_DELETE(base_t, _ret);                                \
	}                                                                  \
	_ret;                                                              \
})//END HAC_AVL_COPY

/**
 * @brief Creates a sequence from a plain old array.
 * Does not deep copy the values in any way.
 * @param base_t the base type.
 * @param size the number of elements to copy from array.
 * @param array the array to copy from (eg an array, a pointer, or the a member of a vector).
 */
#define HAC_SEQ_FROM(base_t, size, array) ({                           \
	size_t _m = (size);                                                \
	base_t *_a;                                                        \
	HAC_SEQ_T(base_t) _ret = HAC_SEQ_EMPTY(base_t);                    \
	for(size_t _i = 0; _i < _m; ++i){                                  \
		if(!__HAC_SEQ_PUSHR_NN(base_t, &_ret, _a[_i])){                \
			HAC_SEQ_DELETE(base_t, &_ret);                             \
			break;                                                     \
		}                                                              \
	}                                                                  \
	if(_ret.a){                                                        \
		_ret.n = _m;                                                   \
	}                                                                  \
	_ret;                                                              \
})//END HAC_SEQ_FROM


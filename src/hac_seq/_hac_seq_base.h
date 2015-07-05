/**@file _hac_seq_base.h*/
/**
 * @brief Deletes a sequence.
 * Frees all nodes and sets the header to empty, but does not delete the values in any way, so HAC_SEQ_FOREACH(base_t, seq, expr) may be needed.
 * @param base_t the base type.
 * @param seq a pointer to the sequence to delete.
 */
#define HAC_SEQ_DELETE(base_t, seq) ({                                 \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	for(__HAC_SEQ_NODE_T(base_t) *_cur = _seq->a, *_next; _cur;){      \
		_next = _cur->b;                                               \
		free(_cur);                                                    \
		_cur = _next;                                                  \
	}                                                                  \
	*_seq = HAC_SEQ_EMPTY(base_t);                                     \
	returnvoid;                                                        \
})//END HAC_SEQ_DELETE

/**
 * @brief Copies a sequence.
 * Does not deep copy the values in any way.
 * @param base_t the base type.
 * @param seq a pointer to the sequence.
 * @return a new sequence that is a copy of seq.
 */
#define HAC_SEQ_COPY(base_t, seq) ({                                   \
	HAC_SEQ_T(base_t) *_seq = (seq), _ret;                             \
	if(_seq->n){                                                       \
		_ret = HAC_SEQ_NEW(base_t, _seq->a->v);                        \
		for(__HAC_SEQ_NODE_T(base_t) *_node = _seq->a->b; _node; _node = _node->b){\
			if(!__HAC_SEQ_PUSHR_NN(base_t, &_ret, _node->v)){          \
				HAC_SEQ_DELETE(base_t, &_ret);                         \
				break;                                                 \
			}                                                          \
		}                                                              \
		if(_ret.a){                                                    \
			_ret.n = _seq->n;                                          \
		}                                                              \
	}else{                                                             \
		_ret = HAC_SEQ_EMPTY(base_t);                                  \
	}                                                                  \
	_ret;                                                              \
})//END HAC_SEQ_COPY

/**
 * @brief Creates a sequence from a plain old array.
 * Does not deep copy the values in any way.
 * @param base_t the base type.
 * @param size the number of elements to copy from array.
 * @param array the array to copy from (eg an array, a pointer, or the a member of a vector).
 * @return a sequence with the first size elements of array.
 */
#define HAC_SEQ_FROM(base_t, size, array) ({                           \
	size_t _m = (size);                                                \
	base_t *_a = array;                                                \
	HAC_SEQ_T(base_t) _ret = HAC_SEQ_EMPTY(base_t);                    \
	for(size_t _i = 0; _i < _m; ++_i){                                 \
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

/**
 * @brief Creates a sequence from an argument list.
 * Variadic macros are cool.
 * @param base_t the base type.
 * @param elems... the elements to put in the sequence.
 * @return a vector with all of the elements in elems..., except base_t obviously.
 */
#define HAC_SEQ_LIST(base_t, elems...) ({                              \
	base_t _a[] = {elems};                                             \
	size_t _m = sizeof(_a)/sizeof(base_t);                             \
	HAC_SEQ_T(base_t) _ret = HAC_SEQ_EMPTY(base_t);                    \
	for(size_t _i = 0; _i < _m; ++_i){                                 \
		if(!__HAC_SEQ_PUSHR_NN(base_t, &_ret, _a[_i])){                \
			HAC_SEQ_DELETE(base_t, &_ret);                             \
			break;                                                     \
		}                                                              \
	}                                                                  \
	if(_ret.a){                                                        \
		_ret.n = _m;                                                   \
	}                                                                  \
	_ret;                                                              \
})//END HAC_SEQ_LIST


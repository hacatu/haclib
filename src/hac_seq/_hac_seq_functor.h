/**@file _hac_seq_functor.h*/
/**
 * @brief Applies an expression to each value in a sequence.
 * Note the values are accessed left to right.
 * @param base_t the base type.
 * @param seq a pointer to the sequence
 * @param expr an expression containing e (the current element)
 */
#define HAC_SEQ_FOREACH(base_t, seq, expr) ({                          \
	base_t e;                                                          \
	for(__HAC_SEQ_NODE_T(base_t) *_node = (seq)->a; _node; _node = _node->b){\
		e = _node->v;                                                  \
		{expr;}                                                        \
	}                                                                  \
	returnvoid;                                                        \
})//END HAC_SEQ_FOREACH

/**
 * @brief Applies an expression to each value in a sequence by pointer.
 * Note the values are accessed left to right.
 * @param base_t the base type.
 * @param seq a pointer to the sequence.
 * @param expr an expression containing e (a pointer to the current element).
 */
#define HAC_SEQ_FOREACHP(base_t, seq, expr) ({                         \
	base_t *e;                                                         \
	for(__HAC_SEQ_NODE_T(base_t) *_node = (seq)->a; _node; _node = _node->b){\
		e = &_node->v;                                                 \
		{expr;}                                                        \
	}                                                                  \
	returnvoid;                                                        \
})//END HAC_SEQ_FOREACHP

/**
 * @brief Creates a new sequence by applying an expression to each value in a sequence.
 * Note the values are processed left to right.
 * @param base_t the base type.
 * @param seq a pointer to the sequence being mapped over.
 * @param expr an expression containing e (the current element).
 */
#define HAC_SEQ_MAP(base_t, seq, expr) ({                              \
	const HAC_SEQ_T(base_t) *_seq = (seq);                             \
	HAC_SEQ_T(base_t) _ret = HAC_SEQ_EMPTY(base_t);                    \
	base_t e;                                                          \
	for(__HAC_SEQ_NODE_T(base_t) *_node = (seq)->a; _node; _node = _node->b){\
		e = _node->v;                                                  \
		if(!__HAC_SEQ_PUSHR_NN(base_t, &_ret, ({expr;}))){             \
			HAC_SEQ_DELETE(base_t, &_ret);                             \
			break;                                                     \
		}                                                              \
	}                                                                  \
	if(_ret.a){                                                        \
		_ret.n = _seq->n;                                              \
	}                                                                  \
	_ret;                                                              \
})//HAC_SEQ_MAP


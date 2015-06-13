/**@file _hac_seq_reverse.h*/
/**
 * @brief Applies expr to a value and every element of a sequence in reverse order, updating the value and then returning it.
 * Note: uses __auto_type, a nonstandard C extension, to determine the type of the accumulator/return value.
 * @param base_t the base type.
 * @param seq a pointer to the sequence to fold.
 * @param init the initial value of the accumulator.  The type of this parameter will be the return type, and expr must process a value of this type and base_t.
 * @param expr an expression containing e (the current element) and l (the last accumulator value, starts as init).
 * @return the final accumulator value.
 */
#define HAC_SEQ_FOLDL(base_t, seq, init, expr) ({                      \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	__auto_type l = (init);                                            \
	base_t e;                                                          \
	for(__HAC_SEQ_NODE_T(base_t) *_node = _seq->b; _node; _node = _node->a){\
		e = _node->v;                                                  \
		l = ({expr;});                                                 \
	}                                                                  \
	l;                                                                 \
})//END HAC_SEQ_FOLDL

/**
 * @brief Removes and returns the leftmost value in a sequence.
 * If the sequence is empty, you will have a bad time (this macro will set a base_t variable to a void value, and that won't work).
 * @param base_t the base type.
 * @param seq a pointer to the sequence.
 * @return the leftmost value, now removed.
 */
#define /*base_t*/HAC_SEQ_POPL(base_t, /*HAC_SEQ_T**/seq) ({           \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	base_t _r;                                                         \
	switch(_seq->n){                                                   \
		case 0:                                                        \
		_r = returnvoid;/*NOTE: fix returnvoid*/                       \
		break;                                                         \
		case 1:                                                        \
		_r = _seq->a->v;                                               \
		free(_seq->a);                                                 \
		_seq->a = _seq->b = NULL;                                      \
		_seq->n = 0;                                                   \
		break;                                                         \
		default:                                                       \
		_r = _seq->a->v;                                               \
		_seq->a = _seq->a->b;                                          \
		free(_seq->a->a);                                              \
		_seq->a->a = NULL;                                             \
		--_seq->n;                                                     \
		break;                                                         \
	}                                                                  \
	_r;                                                                \
})//END HAC_SEQ_POPL

/**
 * @brief Adds a value onto the left end of a sequence.
 * @param base_t the base type.
 * @param seq a pointer to the sequence to prepend to.
 * @param val the value to prepend to the sequence.
 * @return 1 on success, 0 on an allocation failure.
 */
#define /*int*/HAC_SEQ_PUSHL(base_t, /*HAC_SEQ_T**/seq, /*base_t*/val) ({\
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	if(_seq->n){                                                       \
		_seq->a->a = malloc(1*sizeof(__HAC_SEQ_NODE_T(base_t)));       \
		if(_seq->a->a){                                                \
			*_seq->a->a = (__HAC_SEQ_NODE_T(base_t)){.b = _seq->a, .v = (val)};\
			_seq->a = _seq->a->a;                                      \
			++_seq->n;                                                 \
		}                                                              \
	}else{                                                             \
		*_seq = HAC_SEQ_NEW(base_t, (val));                            \
	}                                                                  \
	!!_seq->n;                                                         \
})//END HAC_SEQ_PUSHL


/**@file _hac_seq_forward.h*/
/**
 * @brief Applies expr to a value and every element of a sequence in order, updating the value and then returning it.
 * Note: uses __auto_type, a nonstandard C extension, to determine the type of the accumulator/return value.
 * @param base_t the base type.
 * @param seq a pointer to the sequence to fold.
 * @param init the initial value of the accumulator.  The type of this parameter will be the return type, and expr must process a value of this type and base_t.
 * @param expr an expression containing e (the current element) and l (the last accumulator value, starts as init).
 * @return the final accumulator value.
 */
#define HAC_SEQ_FOLDR(base_t, seq, init, expr) ({                      \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	__auto_type l = (init);                                            \
	__HAC_SEQ_FOREACH(base_t, _seq, ({                                 \
		l = ({expr;});                                                 \
	}));                                                               \
	l;                                                                 \
})//END HAC_SEQ_FOLDR

/**
 * @brief Removes and returns the rightmost value in a sequence.
 * If the sequence is empty, you will have a bad time (this macro will set a base_t variable to a void value, and that won't work).
 * @param base_t the base type.
 * @param seq a pointer to the sequence.
 * @return the rightmost value, now removed.
 */
#define HAC_SEQ_POPR(base_t, seq) ({                                   \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	base_t _r;                                                         \
	switch(_seq->n){                                                   \
		case 0:                                                        \
		_r = returnvoid;/*NOTE: fix returnvoid*/                       \
		break;                                                         \
		case 1:                                                        \
		_r = _seq->b->v;                                               \
		free(_seq->b);                                                 \
		_seq->a = _seq->b = NULL;                                      \
		_seq->n = 0;                                                   \
		break;                                                         \
		default:                                                       \
		_r = _seq->b->v;                                               \
		_seq->b = _seq->b->a;                                          \
		free(_seq->b->b);                                              \
		_seq->b->b = NULL;                                             \
		--_seq->n;                                                     \
		break;                                                         \
	}                                                                  \
	_r;                                                                \
})//END HAC_SEQ_POPR

/**
 * @brief Create an arithmetic sequence of additive values (ie numeric type values).
 * Starts at i1, adds step until i2 is reached, and pushes each value to the end of the sequence.
 * @param base_t the base type.  Must be valid to use with +.
 * @param i1 the starting value (inclusive).
 * @param i2 the ending value (exclusive).
 * @param step the step size.
 * @return an arithmetic sequence with a0 = i1, d = step, and stopping just before i2.
 */
#define HAC_SEQ_RANGE(base_t, i1, i2, step) ({                         \
	base_t _v = (i1), _e = (i2), _s = (step);                          \
	HAC_SEQ_T(base_t) _ret = HAC_SEQ_EMPTY(base_t);                    \
	for(; _v < _e; _v += _s){/*TODO: support negative steps*/          \
		if(!HAC_SEQ_PUSHR(base_t, &_ret, _v)){                         \
			HAC_VEC_DELETE(base_t, &_ret);                             \
			break;                                                     \
		}                                                              \
	}                                                                  \
	_ret;                                                              \
})//END HAC_SEQ_RANGE


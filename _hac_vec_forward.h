/**@file _hac_vec_forward.h*/
/**
 * @brief Applies expr to a value and every element of a vector in order, updating the value and then returning it.
 * Note: uses __auto_type, a nonstandard C extension, to determine the type of the accumulator/return value.
 * @param base_t the base type.
 * @param vec a pointer to the vector to fold.
 * @param init the initial value of the accumulator.  The type of this parameter will be the return type, and expr must process a value of this type and base_t.
 * @param expr an expression containing e (the current element) and l (the last accumulator value, starts as init).
 * @return the final accumulator value.
 */
#define HAC_VEC_FOLDR(base_t, vec, init, expr) ({                      \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	__auto_type l = (init);                                            \
	__HAC_VEC_FOREACH(base_t, _vec, ({                                 \
		l = ({expr;});                                                 \
	}));                                                               \
	l;                                                                 \
})//END HAC_VEC_FOLDR

/**
 * @brief Removes and returns the rightmost value in a vector.
 * If the vector is empty, you will have a bad time (this macro will set a base_t variable to a void value, and that won't work).
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 * @return the rightmost value, now removed.
 */
#define HAC_VEC_POPR(base_t, vec) ({                                   \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	_vec->a[--_vec->n];                                                \
})//END HAC_VEC_POPR

/**
 * @brief Create a vector that is an arithmetic sequence of additive values (ie numeric type values).
 * Starts at i1, adds step until i2 is reached, and pushes each value to the end of the vector.
 * @param base_t the base type.  Must be valid to use with +.
 * @param i1 the starting value (inclusive).
 * @param i2 the ending value (exclusive).
 * @param step the step size.
 * @return a vector that is an arithmetic sequence with a0 = i1, d = step, and stopping just before i2.
 */
#define HAC_VEC_RANGE(base_t, i1, i2, step) ({                         \
	base_t _v = (i1), _s = (step);                                     \
	size_t _n = ((i2) - _v + _s)/_s;                                   \
	HAC_VEC_T(base_t) _ret = __HAC_VEC_NEW(base_t, _n);                \
	if(_ret.a){                                                        \
		for(size_t _i = 0; _i < _n; _v += _s, ++_i){                   \
			_ret.a[_i] = _v;                                           \
		}                                                              \
		_ret.n = _n;                                                   \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_RANGE


/**@file _hac_vec_reverse.h*/
/**
 * @brief Applies expr to a value and every element of a vector in reverse order, updating the value and then returning it.
 * Note: uses __auto_type, a nonstandard C extension, to determine the type of the accumulator/return value.
 * @param base_t the base type.
 * @param vec a pointer to the vector to fold.
 * @param init the initial value of the accumulator.  The type of this parameter will be the return type, and expr must process a value of this type and base_t.
 * @param expr an expression containing e (the current element) and l (the last accumulator value, starts as init).
 * @return the final accumulator value.
 */
#define HAC_VEC_FOLDL(base_t, vec, init, expr) ({                      \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	__auto_type l = (init);                                            \
	base_t e;                                                          \
	for(int _i = _vec->n - 1; _i >= 0; --_i){                          \
		e = _vec->a[_i];                                               \
		l = ({expr;});                                                 \
	}                                                                  \
	l;                                                                 \
})//END HAC_VEC_FOLDL

/**
 * @brief Applies an expression to each value in a vector.
 * Note the values are accessed right to left.
 * @param base_t the base type.
 * @param vec a pointer to the vector
 * @param expr an expression containing e (the current element)
 */
#define /*void*/HAC_VEC_FOREACHL(base_t, /*HAC_VEC_T**/vec, expr) ({   \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	base_t e;                                                          \
	for(int _i = _vec->n - 1; _i >= 0; --_i){                          \
		e = _vec->a[_i];                                               \
		{expr;}                                                        \
	}                                                                  \
	returnvoid;                                                        \
})//END HAC_VEC_FOREACHL


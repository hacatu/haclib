/**@file _hac_vec_functor.h*/
/**
 * @brief Applies an expression to each value in a vector by pointer.
 * Note the values are accessed left to right.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 * @param expr an expression containing e (a pointer to the current element).
 */
#define HAC_VEC_FOREACHP(base_t, vec, expr) ({                         \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	base_t *e;                                                         \
	for(size_t _i = 0; _i < _vec->n; ++_i){                            \
		e = &_vec->a[_i];                                              \
		{expr;}                                                        \
	}                                                                  \
	returnvoid;                                                        \
})//END HAC_VEC_FOREACHP

/**
 * @brief Creates a new vector by applying an expression to each value in a vector.
 * Note the values are processed left to right.
 * @param base_t the base type.
 * @param vec a pointer to the vector being mapped over.
 * @param expr an expression containing e (the current element).
 */
#define HAC_VEC_MAP(base_t, vec, expr) ({                              \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	HAC_VEC_T(base_t) _ret = __HAC_VEC_NEW(base_t, _vec->n);           \
	if(_ret.a){                                                        \
		base_t e;                                                      \
		for(size_t _i = 0; _i < _vec->n; ++_i){                        \
			e = _vec->a[_i];                                           \
			_ret.a[_i] = ({expr;});                                    \
		}                                                              \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_MAP


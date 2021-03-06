/**@file _hac_vec_access.h*/
/**
 * @brief Get the ith value from a vector.
 * Extended get: if the i is negative, use it as a reverse index from the end of the vector.
 * Note this macro is suitable for use as an lvalue.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 * @param i the index.
 * @return the ith element of vec.
 */
#define HAC_VEC_GETX(base_t, vec, i) (*({                              \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	size_t _i = (i);                                                   \
	if(_i < 0){                                                        \
		_i += _vec->n;                                                 \
	}                                                                  \
	&_vec->a[_i];                                                      \
}))//END HAC_VEC_GETX

/**
 * @brief Swap the ith and jth elements of vec.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 * @param i the first index.
 * @param j the second index.
 */
#define HAC_VEC_SWAP(base_t, vec, i, j) ({                             \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	base_t _tmp = _vec->a[i];                                          \
	_vec->a[i] = _vec->a[j];                                           \
	_vec->a[j] = _tmp;                                                 \
	returnvoid;                                                        \
})//END HAC_VEC_SWAP

/**
 * @brief Shuffles a vector.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 * @param swap an expression containing v (a pointer to a vector), i, and j (the indicies to be swapped) (you may use HAC_VEC_SWAP(base_t, vec, i, j) most of the time here).
 * @param expr an expression to generate a random integer between m and n inclusive (I would suggest using a function here).
 */
#define HAC_VEC_SHUFFLE(base_t, vec, swap, expr) ({                    \
	HAC_VEC_T(base_t) *v = (vec);                                      \
	size_t m = 0, n, i, j;                                             \
	for(size_t _i = v->n - 1, _j; _i; --_i){                           \
		n = _i;                                                        \
		_j = ({expr;});                                                \
		i = _i, j = _j;                                                \
		{swap;}                                                        \
	}                                                                  \
})//END HAC_VEC_SHUFFLE


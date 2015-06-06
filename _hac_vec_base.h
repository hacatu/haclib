/**@file _hac_vec_base.h*/
#define /*HAC_VEC_T*/__HAC_VEC_NEW(base_t, /*size_t*/_m) ({            \
	base_t *_a = _m ? malloc(_m*sizeof(base_t)) : NULL;                \
	(HAC_VEC_T(base_t)){.a = _a, .n = 0, .m = _a ? _m : 0};            \
})//END __HAC_VEC_NEW

/**
 * @brief Creates a new vector with space pre-allocated for size elements.
 * Of course more space can be allocated later if the vector grows too large,
 * but this function is intended for use when the final size is known to avoid uneeded reallocs.
 * @param base_t the base type.
 * @param size the number of elements to pre-allocate space for.
 * @return a vector with space for size elements.
 */
#define HAC_VEC_NEW(base_t, size) ({                                   \
	size_t _m = (size);                                                \
	__HAC_VEC_NEW(base_t, _m);                                         \
})//END HAC_VEC_NEW

/**
 * @brief Deletes a vector.
 * Frees the underlying pointer but does not delete values whatsoever, so HAC_VEC_FOREACH(base_t, vec, expr) may be required.
 * Sets vec->n and vec->m to 0 and vec->a to NULL.
 * @param base_t the base type.
 * @param vec a pointer to the vector to delete.
 */
#define HAC_VEC_DELETE(base_t, vec) ({                                 \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	free(_vec->a);                                                     \
	*_vec = (HAC_VEC_T(base_t)){0};                                    \
	returnvoid;                                                        \
})//END HAC_VEC_DELETE

/**
 * @brief Copies a vector.
 * Does not deep copy the values whatsoever.
 * @param base_t the base type.
 * @param vec a pointer to the vector to copy.
 * @return a copy of vec.
 */
#define HAC_VEC_COPY(base_t, vec) ({                                   \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	HAC_VEC_T(base_t) _ret = HAC_VEC_NEW(base_t, _vec->n);             \
	if(_ret.a){                                                        \
		memcpy(_ret.a, _vec->a, _vec->n*sizeof(base_t));               \
		_ret.n = _vec->n;                                              \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_COPY

/**
 * @brief Copies part of a vector.
 * Copies a subrange of a vector starting at the start and going for size elements.  Does not deep copy the values whatsoever.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 * @param size how many elements to copy from vec.
 * @return a copy of the first size elements of vec.
 */
#define HAC_VEC_SUB(base_t, vec, size) ({                              \
	size_t _m = (size);                                                \
	HAC_VEC_T(base_t) _ret = __HAC_VEC_NEW(base_t, _m);                \
	if(_ret.a){                                                        \
		memcpy(_ret.a, vec->a, _m*sizeof(base_t));                     \
		_ret.n = _m;                                                   \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_SUB

/**
 * @brief Creates a vector from plain old array.
 * Does not deep copy the values whatsoever.
 * @param base_t the base type.
 * @param size the number of elements to copy from the array.
 * @param array the array from which to copy the elements.
 * @return a vector with the first size elements of array.
 */
#define HAC_VEC_FROM(base_t, size, array) ({                           \
	size_t _m = (size);                                                \
	HAC_VEC_T(base_t) _ret = __HAC_VEC_NEW(base_t, _m);                \
	if(_ret.a){                                                        \
		memcpy(_ret.a, (array), _m*sizeof(base_t));                    \
		_ret.n = _m;                                                   \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_FROM


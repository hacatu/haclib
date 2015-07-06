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

/**
 * @brief Creates a vector from an argument list.
 * Variadic macros are cool.
 * @param base_t the base type.
 * @param elems... the elements to put in the vector.
 * @return a vector with all of the elements in elems..., except base_t obviously.
 */
#define HAC_VEC_LIST(base_t, elems...) ({                              \
	base_t _arr[] = {elems...};                                        \
	HAC_VEC_T(base_t) _ret = __HAC_VEC_NEW(base_t, sizeof(_arr)/sizeof(base_t));\
	if(_ret.a){                                                        \
		memcpy(_ret.a, _arr, sizeof(_arr));                            \
		_ret.n = sizeof(_arr)/sizeof(base_t);                          \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_LIST

/**
 * @brief Change the storage allocated for a vector.
 * If the specified size is smaller than the used size (NOT allocated size), nothing is done.
 * @param base_t the base type.
 * @param vec a pointer to the vector to increase storage for.
 * @param size the new size.
 * @return 1 on allocation success, 0 on failure.
 */
#define HAC_VEC_RSIZE(base_t, vec, size) ({                            \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	size_t _size = (size);                                             \
	int _ret = 1;                                                      \
	if(_size > _vec->n){                                               \
		base_t *_t = realloc(_vec->a, _size*sizeof(base_t));           \
		if(!_t){                                                       \
			_ret = 0;                                                  \
		}else{                                                         \
			_vec->a = _t;                                              \
			_vec->m = _size;                                           \
		}                                                              \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_RESERVE

/**
 * @brief Reduces allocated storage to used storage.
 * Use optionally when a vector is known to be done growing.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 */
#define HAC_VEC_TRIM(base_t, vec) ({                                   \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	_vec->a = realloc(_vec->a, _vec->n*sizeof(base_t));                \
	_vec->m = _vec->n;                                                 \
})//END HAC_VEC_TRIM

/**
 * @brief Clears a vector without deallocating space.
 * Note that if the elements have dynamic allocations associated with them,
 * they should be cleared first using HAC_VEC_FOREACH.  Also, this does not
 * overwrite existing data at all, just marks the vector as containing 0 elements.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 */
#define HAC_VEC_CLEAR(base_t, vec) ({                                  \
	(vec)->n = 0;                                                      \
})//END HAC_VEC_CLEAR


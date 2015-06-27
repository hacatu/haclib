/**@file _hac_vec_monoid.h*/
/**
 * @brief Checks if a vector is empty.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 * @return 1 if the vector is empty, 0 otherwise.
 */
#define HAC_VEC_IS_EMPTY(base_t, vec) (!(vec)->n)

/**
 * @brief A macro that expands to an empty vector of a type.
 * n and m are 0 and a is NULL.
 * @param base_t the base type.
 * @return an empty vector for base_t.
 */
#define HAC_VEC_EMPTY(base_t) ((HAC_VEC_T(base_t)){0})

/**
 * @brief Combines two vectors to make a new vector.
 * Creates a new vector using HAC_VEC_NEW(base_t, size) with room for all of the elements in veca and vecb
 * and copies their values into it with memcpy().
 * Does not deep copy the values whatsoever.
 * @param base_t the base type.
 * @param veca a pointer to the first vector.
 * @param vecb a pointer to the second vector.
 * @return a combination of the two vector.
 */
#define HAC_VEC_COMBINE(base_t, veca, vecb) ({                         \
	const HAC_VEC_T(base_t) *_a = (veca), *_b = (vecb);                \
	HAC_VEC_T(basse_t) _c = __HAC_VEC_NEW(base_t, _a->n + _b->n);      \
	if(_c.a){                                                          \
		memcpy(_c.a, _a->a, _a->n*sizeof(base_t));                     \
		memcpy(_c.a + _a->n, _b->a, _b->n*sizeof(base_t));             \
		_c.n = _c.m;                                                   \
	}                                                                  \
	_c;                                                                \
})//END HAC_VEC_COMBINE

/**
 * @brief Adds one vector onto the end of another.
 * Extends veca using realloc and copies the values in vecb into it with memcpy().
 * Does not deep copy the values whatsoever.
 * @param base_t the base type.
 * @param veca a pointer to the first vector.
 * @param vecb a pointer to the second vector.
 * @return 1 on success or 0 on allocation failure.
 */
#define HAC_VEC_AUGMENT(base_t, veca, vecb) ({                         \
	HAC_VEC_T(base_t) *_a = (veca), *_b = (vecb);                      \
	base_t *_tmp = realloc(_a->a, (_a->n + _b->n)*sizeof(base_t));     \
	if(_tmp){                                                          \
		_a->a = _tmp;                                                  \
		_a->m = (_a->n + _b->n);                                       \
		memcpy(_a->a + _a->n, _b->a, _b->n*sizeof(base_t));            \
		_a->n = _a->m;                                                 \
	}                                                                  \
	!!_tmp;                                                            \
})//END HAC_VEC_AUGMENT

/**
 * @brief Tests if a condition applies to all elements of a vector.
 * Reads values from left to right and stops early if one does not meet the condition.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 * @param expr an expression containing e (the current element), evaluating to 1 if true and 0 if false.
 * @return 1 if the condition is 1 for all elements of the vector, 0 otherwise.
 */
#define HAC_VEC_ALL(base_t, vec, expr) ({                              \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	int _r = 1;                                                        \
	base_t e;                                                          \
	for(size_t _i = 0; _r && _i < _vec->n; ++_i){                      \
		e = _vec->a[_i];                                               \
		_r = _r && ({expr;});                                          \
	}                                                                  \
	_r;                                                                \
})//END HAC_VEC_ALL

/**
 * @brief Tests if a condition applies to any element in a vector.
 * Reads values from left to right and stops early if one meets the condition.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 * @param expr an expression containing e (the current element), evaluating to 1 if true and 0 if false.
 * @return 1 if the condition is 1 for any element in the sequence, 0 otherwise.
 */
#define HAC_VEC_ANY(base_t, vec, expr) ({                              \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	int _r = 0;                                                        \
	base_t e;                                                          \
	for(size_t _i = 0; (!_r) && _i < _vec->n; ++_i){                   \
		e = _vec->a[_i];                                               \
		_r = _r || ({expr;});                                          \
	}                                                                  \
	_r;                                                                \
})//END HAC_VEC_ANY

/**
 * @brief Tests if a value contains a value.
 * Reads values from left to right and stops early if one matches.
 * Note that this is O(n) time and if you want to do a lot of checks like this you should look into using a different data structure.
 * @param base_t the base type.
 * @param vec a pointer to the vector.
 * @param elem the value to check for in the vector.
 * @param comp an expression containing e1 and e2 (the two elements to be compared) and returning 0 if they are equal.
 * @return 1 if elem is in vec, 0 otherwise.
 */
#define HAC_VEC_CONTAINS(base_t, vec, elem, comp) HAC_VEC_ANY(base_t, vec, ({base_t e1 = elem; base_t e2 = e; !({comp});}))


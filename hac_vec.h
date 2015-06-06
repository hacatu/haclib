/**
 * @file hac_vec.h
 * @brief Self-resizing array data type.
 */
#ifndef __HAC_VEC__
#define __HAC_VEC__

#include <stdlib.h>
#include <string.h>
#include "hac_util.h"
#include "hac_pair.h"

#ifndef HAC_VEC_G_RATIO
/**
 * The ratio to grow vectors by whenever their underlying buffer is not big enough.
 */
#define HAC_VEC_G_RATIO 2
#endif

#define __HAC_VEC_T(base_t) __HAC_VEC_##base_t##_T

/**
 * @brief A macro that represents the type of a vector of types.
 * Expands to an identifier of the form __HAC_VEC_##base_t##_T, which has been typedefed by HAC_VEC_T_NEW(base_t).
 * @param base_t the base type of the vector, eg double for a vector of doubles.
 * @return an identifier of the form __HAC_VEC_##base_t##_T.
 */
#define HAC_VEC_T(base_t) __HAC_VEC_T(base_t)

/**
 * @brief Sets up the typedef for HAC_VEC_T(base_t).
 * HAC_VEC_T(base_t) is typedefed to be a struct with three members: n (the number of elements), a (a pointer to the underlying buffer), and m (the maximum number of elements the buffer can hold).
 * @param base_t the base type.
 */
#define HAC_VEC_T_NEW(base_t) typedef struct{base_t *a; size_t n, m;} HAC_VEC_T(base_t)

/**
 * @brief Gets the ith element of a vector.
 * Equivalent to (vec)->a[i], so you can just use that if you'd prefer.  Does not do bounds checking.
 * Does not handle negative indicies: for those, try HAC_VEC_GETX(base_t, vec, i).
 * @param base_t the base type.  (ignored).
 * @param vec a pointer to the vector.
 * @param i the index.
 * @return the ith element of vec.
 */
#define HAC_VEC_GET(base_t, vec, i) ((vec)->a[i])

/**
 * @brief Gets the length of a vector.
 * Equivalent to (vec)->n, so you can just use that if you'd prefer.
 * @param base_t the base type.  (ignored).
 * @param vec a pointer to the vector.
 * @return the number of elements in vec.
 */
#define HAC_VEC_LEN(base_t, vec) ((vec)->n)

#define /*void*/__HAC_VEC_FOREACH(base_t, /*HAC_VEC_T**/_vec, expr) ({ \
	base_t e;                                                          \
	for(size_t _i = 0; _i < _vec->n; ++_i){                            \
		e = _vec->a[_i];                                               \
		{expr;}                                                        \
	}                                                                  \
	returnvoid;                                                        \
})//END __HAC_VEC_FOREACH

/**
 * @brief Applies an expression to each value in a vector.
 * Note the values are accessed left to right.
 * @param base_t the base type.
 * @param vec a pointer to the vector
 * @param expr an expression containing e (the current element)
 */
#define HAC_VEC_FOREACH(base_t, vec, expr) ({                          \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	__HAC_VEC_FOREACH(base_t, _vec, expr);                             \
})//END HAC_VEC_FOREACH

/**
 * @brief Adds a value onto the right end of a vector.
 * @param base_t the base type.
 * @param vec a pointer to the vector to append to.
 * @param v the value to append to the vector.
 * @return 1 on success, 0 on an allocation failure.
 */
#define HAC_VEC_PUSHR(base_t, vec, v) ({                               \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	base_t *_tmp = _vec->a;                                            \
	if(_vec->n + 1 > _vec->m){                                         \
		if(_vec->m){                                                   \
			_tmp = realloc(_vec->a, _vec->m*HAC_VEC_G_RATIO*sizeof(base_t));\
			if(_tmp){                                                  \
				_vec->a = _tmp;                                        \
				_vec->m *= HAC_VEC_G_RATIO;                            \
			}                                                          \
		}else{                                                         \
			_vec->a = malloc(1*sizeof(base_t));                        \
			if(_vec->a){                                               \
				_tmp = _vec->a;                                        \
				_vec->m = 1;                                           \
			}                                                          \
		}                                                              \
	}                                                                  \
	if(_tmp){                                                          \
		_vec->a[_vec->n++] = (v);                                      \
	}                                                                  \
	!!_tmp;                                                            \
})//END HAC_VEC_PUSHR

#include "_hac_vec_base.h"
#include "_hac_vec_functor.h"
#include "_hac_vec_monoid.h"
#include "_hac_vec_collection.h"
#include "_hac_vec_forward.h"
#include "_hac_vec_reverse.h"
#include "_hac_vec_access.h"
#include "_hac_vec_sortable.h"

#endif


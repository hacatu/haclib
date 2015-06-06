//hac_ve.h
#ifndef __HAC_VEC__
#define __HAC_VEC__

#include <stdlib.h>
#include <string.h>
#include "hac_util.h"
#include "hac_pair.h"

#ifndef HAC_VEC_G_RATIO
#define HAC_VEC_G_RATIO 2
#endif

#define __HAC_VEC_T(base_t) __HAC_VEC_##base_t##_T
#define HAC_VEC_T(base_t) __HAC_VEC_T(base_t)

#define HAC_VEC_T_NEW(base_t) typedef struct{base_t *a; size_t n, m;} HAC_VEC_T(base_t)

#define /*base_t*/HAC_VEC_GET(base_t, /*HAC_VEC_T**/vec, /*size_t*/i) ((vec)->a[i])
#define /*size_t*/HAC_VEC_LEN(base_t, /*HAC_VEC_T**/vec) ((vec)->n)
#define /*void*/__HAC_VEC_FOREACH(base_t, /*HAC_VEC_T**/_vec, expr) ({ \
	base_t e;                                                          \
	for(size_t _i = 0; _i < _vec->n; ++_i){                            \
		e = _vec->a[_i];                                               \
		{expr;}                                                        \
	}                                                                  \
	returnvoid;                                                        \
})//END __HAC_VEC_FOREACH
//expr is an expression containing e (the current element)
#define /*void*/HAC_VEC_FOREACH(base_t, /*HAC_VEC_T**/vec, expr) ({    \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	__HAC_VEC_FOREACH(base_t, _vec, expr);                             \
})//END HAC_VEC_FOREACH
#define /*int*/HAC_VEC_PUSHR(base_t, /*HAC_VEC_T**/vec, /*base_t*/v) ({\
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	base_t *_tmp = _vec->a;                                            \
	if(_vec->n + 1 > _vec->m){                                         \
		_tmp = realloc(_vec->a, _vec->m*HAC_VEC_G_RATIO*sizeof(base_t));\
		if(_tmp){                                                      \
			_vec->a = _tmp;                                            \
			_vec->m *= HAC_VEC_G_RATIO;                                \
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


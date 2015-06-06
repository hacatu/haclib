//hac_pair.h
#ifndef __HAC_PAIR__
#define __HAC_PAIR__

#include "hac_util.h"

#define HAC_PAIR_T_NEW(base_t) typedef struct{base_t a, b;} __HAC_PAIR_##base_t##_T

#define HAC_PAIR_T(base_t) __HAC_PAIR_##base_t##_T

#define /*HAC_PAIR_T*/HAC_PAIR_MAKE(base_t, /*base_t*/_a, /*base_t*/_b) (HAC_PAIR_T(base_t)){.a = _a, .b = _b}
#define /*HAC_PAIR_T**/HAC_PAIR_SWAP(base_t, /*HAC_PAIR_T**/pair) ({   \
	HAC_PAIR_T(base_t) *_p = (pair);                                   \
	base_t _t = _p->a;                                                 \
	_p->a = _p->b;                                                     \
	_p->b = _t;                                                        \
	_p;                                                                \
})//END HAC_PAIR_SWAP
#define /*HAC_PAIR_T*/HAC_PAIR_COPY(base_t, /*HAC_PAIR_T**/pair) ({    \
	HAC_PAIR_T(base_t) *_p = (pair);                                   \
	HAC_PAIR_MAKE(base_t, _p->a, _p->b);                               \
})//END HAC_PAIR_COPY

#endif


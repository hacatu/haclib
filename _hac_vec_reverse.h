//_hac_vec_forward.h
//expr is an expression containing e (the current element) and l (the last accumulator value)
#define HAC_VEC_FOLDL(base_t, /*HAC_VEC_T**/vec, init, expr) ({        \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	__auto_type l = (init);                                            \
	base_t e;                                                          \
	for(int _i = _vec->n - 1; _i >= 0; --_i){                          \
		e = _vec->a[_i];                                               \
		l = ({expr;});                                                 \
	}                                                                  \
	l;                                                                 \
})//END HAC_VEC_FOLDL
//expr is an expression containing e (the current element)
#define /*void*/HAC_VEC_FOREACHL(base_t, /*HAC_VEC_T**/vec, expr) ({   \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	base_t e;                                                          \
	for(int _i = _vec->n - 1; _i >= 0; --_i){                          \
		e = _vec->a[_i];                                               \
		{expr;}                                                        \
	}                                                                  \
	returnvoid;                                                        \
})//END HAC_VEC_FOREACHL


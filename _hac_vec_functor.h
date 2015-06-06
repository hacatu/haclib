//_hac_vec_functor.h
//expr is an expression containing e (a pointer to the current element)
#define /*void*/HAC_VEC_FOREACHP(base_t, /*HAC_VEC_T**/vec, expr) ({   \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	base_t *e;                                                         \
	for(size_t _i = 0; _i < _vec->n; ++_i){                            \
		e = &_vec->a[_i];                                              \
		{expr;}                                                        \
	}                                                                  \
	returnvoid;                                                        \
})//END HAC_VEC_FOREACHP
//expr is an expression contatining e (the current element)
#define /*HAC_VEC_T*/HAC_VEC_MAP(base_t, /**HAC_VEC_T**/vec, expr) ({  \
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


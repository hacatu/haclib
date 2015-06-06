//_hac_vec_forward.h
//expr is an expression containing e (the current element) and l (the last accumulator value)
#define HAC_VEC_FOLDR(base_t, /*HAC_VEC_T**/vec, init, expr) ({        \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	__auto_type l = (init);                                            \
	__HAC_VEC_FOREACH(base_t, _vec, ({                                 \
		l = ({expr;});                                                 \
	}));                                                               \
	l;                                                                 \
})//END HAC_VEC_FOLDR
#define /*base_t*/HAC_VEC_POPR(base_t, /*HAC_VEC_T**/vec) ({           \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	_vec->a[--_vec->n];                                                \
})//END HAC_VEC_POPR
#define /*HAC_VEC_T*/HAC_VEC_RANGE(base_t, /*base_t*/i1, /*base_t*/i2, /*base_t*/step) ({\
	base_t _v = (i1), _s = (step);                                     \
	size_t _n = ((i2) - _v + _s)/_s;                                   \
	HAC_VEC_T(base_t) _ret = __HAC_VEC_NEW(base_t, _n);                \
	if(_ret.a){                                                        \
		for(size_t _i = 0; _i < _n; _v += _s, ++_i){                   \
			_ret.a[_i] = _v;                                           \
		}                                                              \
		_ret.n = _n;                                                   \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_RANGE


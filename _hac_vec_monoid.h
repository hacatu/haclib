//_hac_vec_monoid.h
#define /*int*/HAC_VEC_IS_EMPTY(base_t, /*HAC_VEC_T**/vec) (!(vec)->n)
#define /*HAC_VEC_T*/HAC_VEC_EMPTY(base_t) ((HAC_VEC_T(base_t)){0})
#define /*HAC_VEC_T*/HAC_VEC_COMBINE(base_t, veca, vecb) ({            \
	const HAC_VEC_T(base_t) *_a = (veca), *_b = (vecb);                \
	HAC_VEC_T(basse_t) _c = __HAC_VEC_NEW(base_t, _a->n + _b->n);      \
	if(_c.a){                                                          \
		memcpy(_c.a, _a->a, _a->n*sizeof(base_t));                     \
		memcpy(_c.a + _a->n, _b->a, _b->n*sizeof(base_t));             \
		_c.n = _c.m;                                                   \
	}                                                                  \
	_c;                                                                \
})//END HAC_VEC_COMBINE
#define /*int*/HAC_VEC_AUGMENT(base_t, veca, vecb) ({                  \
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
//expr is an expression containing e (the current element)
#define /*int*/HAC_VEC_ALL(base_t, vec, expr) ({                       \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	int _r = 1;                                                        \
	base_t e;                                                          \
	for(size_t _i = 0; _r && _i < _vec->n; ++_i){                      \
		e = _vec->a[_i];                                               \
		_r = _r && ({expr;});                                          \
	}                                                                  \
	_r;                                                                \
})//END HAC_VEC_ALL
//expr is an expression containing e (the current element)
#define /*int*/HAC_VEC_ANY(base_t, vec, expr) ({                       \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	int _r = 0;                                                        \
	base_t e;                                                          \
	for(size_t _i = 0; (!_r) && _i < _vec->n; ++_i){                   \
		e = _vec->a[_i];                                               \
		_r = _r || ({expr;});                                          \
	}                                                                  \
	_r;                                                                \
})//END HAC_VEC_ANY
//comp is an expression containing e1 and e2 (the two elements being compared)
#define /*int*/HAC_VEC_CONTAINS(base_t, /*HAC_VEC_T**/vec, /*base_t*/elem, comp) HAC_VEC_ANY(base_t, vec, ({base_t e1 = elem; base_t e2 = e; !({comp});}))


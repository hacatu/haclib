//_hac_vec_base.h
#define /*HAC_VEC_T*/__HAC_VEC_NEW(base_t, /*size_t*/_m) ({            \
	base_t *_a = _m ? malloc(_m*sizeof(base_t)) : NULL;                \
	(HAC_VEC_T(base_t)){.a = _a, .n = 0, .m = _a ? _m : 0};            \
})//END __HAC_VEC_NEW
#define /*HAC_VEC_T*/HAC_VEC_NEW(base_t, /*size_t*/size) ({            \
	size_t _m = (size);                                                \
	__HAC_VEC_NEW(base_t, _m);                                         \
})//END HAC_VEC_NEW
#define /*void*/HAC_VEC_DELETE(base_t, /*HAC_VEC_T**/vec) ({           \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	free(_vec->a);                                                     \
	*_vec = (HAC_VEC_T(base_t)){0};                                    \
	returnvoid;                                                        \
})//END HAC_VEC_DELETE
#define /*HAC_VEC_T*/HAC_VEC_COPY(base_t, /*HAC_VEC_T**/vec) ({        \
	const HAC_VEC_T(base_t) *_vec = (vec);                             \
	HAC_VEC_T(base_t) _ret = HAC_VEC_NEW(base_t, _vec->n);             \
	if(_ret.a){                                                        \
		memcpy(_ret.a, _vec->a, _vec->n*sizeof(base_t));               \
		_ret.n = _vec->n;                                              \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_COPY
#define /*HAC_VEC_T*/HAC_VEC_SUB(base_t, /*HAC_VEC_T**/vec, /*size_t*/size) ({\
	size_t _m = (size);                                                \
	HAC_VEC_T(base_t) _ret = __HAC_VEC_NEW(base_t, _m);                \
	if(_ret.a){                                                        \
		memcpy(_ret.a, vec->a, _m*sizeof(base_t));                     \
		_ret.n = _m;                                                   \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_SUB
#define /*HAC_VEC_T*/HAC_VEC_FROM(base_t, /*size_t*/size, array) ({    \
	size_t _m = (size);                                                \
	HAC_VEC_T(base_t) _ret = __HAC_VEC_NEW(base_t, _m);                \
	if(_ret.a){                                                        \
		memcpy(_ret.a, (array), _m*sizeof(base_t));                    \
		_ret.n = _m;                                                   \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_FROM


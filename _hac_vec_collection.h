//_hac_vec_collection.h
//expr is an expression contatining e (the current element)
#define /*HAC_VEC_T*/HAC_VEC_FILTER(base_t, /*HAC_VEC_T**/vec, expr) ({\
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	HAC_VEC_T(base_t) _ret = HAC_VEC_NEW(base_t, _vec->n);             \
	if(_ret.a){                                                        \
		__HAC_VEC_FOREACH(base_t, _vec, ({                             \
			if(({expr;})){                                             \
				HAC_VEC_PUSHR(base_t, &_ret, e);                       \
			}                                                          \
			returnvoid;                                                \
		}));                                                           \
	}                                                                  \
	_ret;                                                              \
})//END HAC_VEC_FILTER


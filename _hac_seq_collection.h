//_hac_seq_collection.h
//expr is an expression contatining e (the current element)
#define /*HAC_SEQ_T*/HAC_SEQ_FILTER(base_t, /*HAC_SEQ_T**/seq, expr) ({\
	HAC_SEQ_T(base_t) _ret = HAC_SEQ_EMPTY(base_t);                    \
	base_t e;                                                          \
	HAC_SEQ_FOREACH(base_t, seq, ({                                    \
		if(({expr;})){                                                 \
			HAC_SEQ_PUSHR(base_t, &_ret, e);                           \
		}                                                              \
		returnvoid;                                                    \
	}));                                                               \
	_ret;                                                              \
})//END HAC_VEC_FILTER


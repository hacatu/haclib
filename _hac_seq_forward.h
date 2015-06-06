//_hac_seq_forward.h
//expr is an expression containing e (the current element) and l (the last accumulator value)
#define HAC_SEQ_FOLDR(base_t, /*HAC_SEQ_T**/seq, init, expr) ({        \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	__auto_type l = (init);                                            \
	__HAC_SEQ_FOREACH(base_t, _seq, ({                                 \
		l = ({expr;});                                                 \
	}));                                                               \
	l;                                                                 \
})//END HAC_SEQ_FOLDR
#define /*base_t*/HAC_SEQ_POPR(base_t, /*HAC_SEQ_T**/seq) ({           \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	base_t _r;                                                         \
	switch(_seq->n){                                                   \
		case 0:                                                        \
		_r = returnvoid;/*NOTE: fix returnvoid*/                       \
		break;                                                         \
		case 1:                                                        \
		_r = _seq->b->v;                                               \
		free(_seq->b);                                                 \
		_seq->a = _seq->b = NULL;                                      \
		_seq->n = 0;                                                   \
		break;                                                         \
		default:                                                       \
		_r = _seq->b->v;                                               \
		_seq->b = _seq->b->a;                                          \
		free(_seq->b->b);                                              \
		_seq->b->b = NULL;                                             \
		--_seq->n;                                                     \
		break;                                                         \
	}                                                                  \
	_r;                                                                \
})//END HAC_SEQ_POPR
#define /*HAC_SEQ_T*/HAC_SEQ_RANGE(base_t, /*base_t*/i1, /*base_t*/i2, /*base_t*/step) ({\
	base_t _v = (i1), _e = (i2), _s = (step);                          \
	HAC_SEQ_T(base_t) _ret = HAC_SEQ_EMPTY(base_t);                    \
	for(; _v < _e; _v += _s){                                          \
		if(!HAC_SEQ_PUSHR(base_t, &_ret, _v)){                         \
			HAC_VEC_DELETE(base_t, &_ret);                             \
			break;                                                     \
		}                                                              \
	}                                                                  \
	_ret;                                                              \
})//END HAC_SEQ_RANGE


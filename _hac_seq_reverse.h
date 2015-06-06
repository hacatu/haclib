//_hac_seq_forward.h
//expr is an expression containing e (the current element) and l (the last accumulator value)
#define HAC_SEQ_FOLDL(base_t, /*HAC_SEQ_T**/seq, init, expr) ({        \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	__auto_type l = (init);                                            \
	base_t e;                                                          \
	for(__HAC_SEQ_NODE_T(base_t) *_node = _seq->b; _node; _node = _node->a){\
		e = _node->v;                                                  \
		l = ({expr;});                                                 \
	}                                                                  \
	l;                                                                 \
})//END HAC_SEQ_FOLDL
#define /*base_t*/HAC_SEQ_POPL(base_t, /*HAC_SEQ_T**/seq) ({           \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	base_t _r;                                                         \
	switch(_seq->n){                                                   \
		case 0:                                                        \
		_r = returnvoid;/*NOTE: fix returnvoid*/                       \
		break;                                                         \
		case 1:                                                        \
		_r = _seq->a->v;                                               \
		free(_seq->a);                                                 \
		_seq->a = _seq->b = NULL;                                      \
		_seq->n = 0;                                                   \
		break;                                                         \
		default:                                                       \
		_r = _seq->a->v;                                               \
		_seq->a = _seq->a->b;                                          \
		free(_seq->a->a);                                              \
		_seq->a->a = NULL;                                             \
		--_seq->n;                                                     \
		break;                                                         \
	}                                                                  \
	_r;                                                                \
})//END HAC_SEQ_POPL
#define /*int*/HAC_SEQ_PUSHR(base_t, /*HAC_SEQ_T**/seq, /*base_t*/val) ({
	HAC_SEQ_T(base_t) *_seq = (seq);
	if(_seq->n){
		_seq->a->a = malloc(1*sizeof(__HAC_SEQ_NODE_T(base_t)));
		if(_seq->a->a){
			*_seq->a->a = (__HAC_SEQ_NODE_T(base_t)){.b = _seq->a, .v = (val)};
			_seq->a = _seq->a->a;
			++_seq->n;
		}
	}else{
		*_seq = HAC_SEQ_NEW(base_t, (val));
	}
	!!_seq->n;
})


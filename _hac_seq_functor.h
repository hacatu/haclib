//_hac_seq_functor.h
//expr is an expression containing e (the current element)
#define /*void*/HAC_SEQ_FOREACH(base_t, /*HAC_SEQ_T**/seq, expr) ({    \
	base_t e;                                                          \
	for(__HAC_SEQ_NODE_T(base_t) *_node = (seq)->a; _node; _node = _node->b){\
		e = _node->v;                                                  \
		{expr;}                                                        \
	}                                                                  \
	returnvoid;                                                        \
})//END HAC_SEQ_FOREACH
//expr is an expression containing e (a pointer to the current element)
#define /*void*/HAC_SEQ_FOREACHP(base_t, /*HAC_SEQ_T**/seq, expr) ({   \
	base_t *e;                                                         \
	for(__HAC_SEQ_NODE_T(base_t) *_node = (seq)->a; _node; _node = _node->b){\
		e = &_node->v;                                                 \
		{expr;}                                                        \
	}                                                                  \
	returnvoid;                                                        \
})//END HAC_SEQ_FOREACHP
//expr is an expression containing e (the current element)
#define /*HAC_SEQ_T*/HAC_SEQ_MAP(base_t, /*HAC_SEQ_T**/seq, expr) ({   \
	const HAC_SEQ_T(base_t) *_seq = (seq);                             \
	HAC_SEQ_T(base_t) _ret = HAC_SEQ_EMPTY(base_t);                    \
	base_t e;                                                          \
	for(__HAC_SEQ_NODE_T(base_t) *_node = (seq)->a; _node; _node = _node->b){\
		e = _node->v;                                                  \
		if(!__HAC_SEQ_PUSHR_NN(base_t, &_ret, ({expr;}))){             \
			HAC_SEQ_DELETE(base_t, &_ret);                             \
			break;                                                     \
		}                                                              \
	}                                                                  \
	if(_ret.a){                                                        \
		_ret.n = _seq->n;                                              \
	}                                                                  \
	_ret;                                                              \
})//HAC_SEQ_MAP


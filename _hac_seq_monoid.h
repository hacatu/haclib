//_hac_seq_monoid.h
#define /*int*/HAC_SEQ_IS_EMPTY(base_t, /*HAC_SEQ_T**/seq) (!(seq)->n)
#define /*void*/__HAC_SEQ_MERGE(base_t, /*HAC_SEQ_T**/seqa, /*HAC_SEQ_T**/seqb) ({\
	if((seqa)->n && (seqb)->n){                                        \
		(seqa)->b->b = (seqb)->a;                                      \
		(seqb)->a->a = (seqa)->b;                                      \
		(seqb)->a = (seqa)->a;                                         \
		(seqa)->b = (seqb)->b;                                         \
		(seqa)->n = (seqb)->n;                                         \
	}                                                                  \
})//END __HAC_SEQ_MERGE
#define /*void*/HAC_SEQ_MERGE(base_t, /*HAC_SEQ_T**/seqa, /*HAC_SEQ_T**/seqb) ({\
	HAC_SEQ_T(base_t) *_seqa = (seqa), *_seqb = (seqb);                \
	__HAC_SEQ_MERGE(base_t, _seqa, _seqb);                             \
})//END HAC_SEQ_MERGE
#define /*HAC_SEQ_T*/HAC_SEQ_COMBINE(base_t, /*HAC_SEQ_T**/seqa, /*HAC_SEQ_T**/seqb) ({\
	HAC_SEQ_T(base_t) _seqa = HAC_SEQ_COPY(base_t, (seqa)), _seqb = HAC_SEQ_COPY(base_t, (seqb));\
	__HAC_SEQ_MERGE(base_t, &_seqa, &_seqb);                           \
	_seqa;                                                             \
})//END HAC_SEQ_COMBINE
//expr is an expression containing e (the current element)
#define /*int*/HAC_SEQ_ALL(base_t, /*HAC_SEQ_t**/seq, expr) ({         \
	const HAC_SEQ_T(base_t) *_seq = (seq);                             \
	int _r = 1;                                                        \
	base_t e;                                                          \
	for(__HAC_SEQ_NODE_T(base_t) *_node = _seq->a; _r && _node; _node = _node->b){\
		e = _node->v;                                                  \
		_r = _r && ({expr;});                                          \
	}                                                                  \
	_r;                                                                \
})//END HAC_SEQ_ALL
//expr is an expression containing e (the current element)
#define /*int*/HAC_SEQ_ANY(base_t, /*HAC_SEQ_t**/seq, expr) ({         \
	const HAC_SEQ_T(base_t) *_seq = (seq);                             \
	int _r = 0;                                                        \
	base_t e;                                                          \
	for(__HAC_SEQ_NODE_T(base_t) *_node = _seq->a; (!_r) && _node; _node = _node->b){\
		e = _node->v;                                                  \
		_r = _r || ({expr;});                                          \
	}                                                                  \
	_r;                                                                \
})//END HAC_SEQ_ANY
//comp is an expression containing e1 and e2 (the two elements being compared)
#define /*int*/HAC_SEQ_CONTAINS(base_t, /*HAC_SEQ_T**/seq, /*base_t*/elem, comp) HAC_VEC_ANY(base_t, vec, ({base_t e1 = elem; base_t e2 = e; !({comp});}))


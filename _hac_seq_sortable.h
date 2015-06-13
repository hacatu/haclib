/**@file _hac_seq_sortable.h*/
#define /*__HAC_SEQ_NODE_T**/__HAC_SEQ_MERGE_SORTED(base_t, /*__HAC_SEQ_NODE_T**/na, /*__HAC_SEQ_NODE_T**/nb, /*size_t*/sa, /*size_t*/sb, comp) ({\
	size_t _a = sa, _b = sb;                                           \
	__HAC_SEQ_NODE_T(base_t) *_s, *_n;                                 \
	base_t e1, e2;                                                     \
	if(({e1 = na->v; e2 = nb->v; comp;}) < 0){                         \
		_s = _n = na;                                                  \
		na = na->b;                                                    \
		--_a;                                                          \
	}else{                                                             \
		_s = _n = nb;                                                  \
		nb = nb->b;                                                    \
		--_b;                                                          \
	}                                                                  \
	while(_a && _b){                                                   \
		if(({e1 = na->v; e2 = nb->v; comp;}) < 0){                     \
			_n->b = na;                                                \
			_n = _n->b;                                                \
			na = na->b;                                                \
			--_a;                                                      \
		}else{                                                         \
			_n->b = nb;                                                \
			_n = _n->b;                                                \
			nb = nb->b;                                                \
			--_b;                                                      \
		}                                                              \
	}                                                                  \
	if(_a){                                                            \
		_n->b = na;                                                    \
	}else if(_b){                                                      \
		_n->b = nb;                                                    \
	}                                                                  \
	_s;                                                                \
})//END __HAC_SEQ_MERGE_SORTED

#define /*void*/__HAC_SEQ_MSTEP(base_t, /*HAC_SEQ_T**/seq, /*__HAC_SEQ_NODE_T**/nodes, /*size_t*/step, comp) ({\
	for(size_t _i = 0, _j = step; _j < (seq)->n; _i += 2*step, _j += 2*step){\
		(nodes)[_i] = __HAC_SEQ_MERGE_SORTED(base_t, (nodes)[_i], (nodes)[_j], step, ((seq)->n - _j < step) ? ((seq)->n - _j) : step, comp);\
	}                                                                  \
})//END __HAC_SEQ_MSTEP

#define /*void*/__HAC_SEQ_MSORT(base_t, /*HAC_SEQ_T**/seq, comp) ({    \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	/*TODO: reduce memory requirements*/                               \
	__HAC_SEQ_NODE_T(base_t) **_nodes = malloc((_seq->n)*sizeof(__HAC_SEQ_NODE_T(base_t)*));\
	if(_nodes){                                                        \
		size_t _i = 0;                                                 \
		/*NOTE: I shouldn't be using _node from HAC_SEQ_FOREACH like this*/\
		HAC_SEQ_FOREACH(base_t, _seq, ({(void)e; _nodes[_i++] = _node;}));\
		for(size_t _s = 1; _s < _seq->n; _s *= 2){                     \
			__HAC_SEQ_MSTEP(base_t, _seq, _nodes, _s, comp);           \
		}                                                              \
		free(_nodes);                                                  \
		__HAC_SEQ_FIXP(base_t, _seq);                                  \
	}                                                                  \
})//END __HAC_SEQ_MSORT

/**
 * @brief Sorts a sequence.
 * Uses merge sort.
 * @param base_t the base type.
 * @param seq a pointer to the sequence to sort
 * @param comp an expression containing e1 and e2 (the elements to be compared).  Should evaluate < 0 if e1 < e2, > 0 if e1 > e2, and == 0 if e1 == e2.  Remember that just using - will sometimes cause overflow.
 */
#define HAC_SEQ_SORT(base_t, seq, comp) __HAC_SEQ_MSORT(base_t, seq, comp);


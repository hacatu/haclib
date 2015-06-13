/**@file _hac_seq_shuffle.h*/
#define /*__HAC_SEQ_NODE_T**/__HAC_SEQ_SHUFFLE_MERGE(base_t, /*__HAC_SEQ_NODE_T**/na, /*__HAC_SEQ_NODE_T**/nb, /*size_t*/sa, /*size_t*/sb, rand) ({\
	size_t _a = sa, _b = sb;                                           \
	__HAC_SEQ_NODE_T(base_t) *_s, *_n;                                 \
	if(({rand;}) < _a/(double)(_a + _b)){                              \
		_s = _n = na;                                                  \
		na = na->b;                                                    \
		--_a;                                                          \
	}else{                                                             \
		_s = _n = nb;                                                  \
		nb = nb->b;                                                    \
		--_b;                                                          \
	}                                                                  \
	while(_a && _b){                                                   \
		if(({rand;}) < _a/(double)(_a + _b)){                          \
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
})//END __HAC_SEQ_SHUFFLE_MERGE

#define /*void*/__HAC_SEQ_SHUFFLE_STEP(base_t, /*HAC_SEQ_T**/seq, /*__HAC_SEQ_NODE_T**/nodes, /*size_t*/step, rand) ({\
	for(size_t _i = 0, _j = step; _j < (seq)->n; _i += 2*step, _j += 2*step){\
		(nodes)[_i] = __HAC_SEQ_SHUFFLE_MERGE(base_t, (nodes)[_i], (nodes)[_j], step, ((seq)->n - _j < step) ? ((seq)->n - _j) : step, rand);\
	}                                                                  \
})//END __HAC_SEQ_SHUFFLE_STEP

/**
 * @brief Shuffles a sequence.
 * Uses merge sort.
 * @param base_t the base type.
 * @param seq a pointer to the sequence to shuffle
 * @param rand an expression that returns a double between [0,1).
 */
#define HAC_SEQ_SHUFFLE(base_t, seq, rand) ({                          \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	/*TODO: reduce memory requirements*/                               \
	__HAC_SEQ_NODE_T(base_t) **_nodes = malloc((_seq->n)*sizeof(__HAC_SEQ_NODE_T(base_t)*));\
	if(_nodes){                                                        \
		size_t _i = 0;                                                 \
		/*NOTE: I shouldn't be using _node from HAC_SEQ_FOREACH like this*/\
		HAC_SEQ_FOREACH(base_t, _seq, ({(void)e; _nodes[_i++] = _node;}));\
		for(size_t _s = 1; _s < _seq->n; _s *= 2){                     \
			__HAC_SEQ_SHUFFLE_STEP(base_t, _seq, _nodes, _s, rand);    \
		}                                                              \
		free(_nodes);                                                  \
		__HAC_SEQ_FIXP(base_t, _seq);                                  \
	}                                                                  \
})//END HAC_SEQ_SHUFFLE


/**@file _hac_seq_sortable.h*/
/*TODO: Yes, this really needs zippers.  Because complexity is good, right?*/
#define /*void*/__HAC_SEQ_REMOVE(base_t, /*HAC_SEQ_T**/_seq, /*__HAC_SEQ_NODE_T**/_c) ({\
	/*does not null the a and b pointers of the node removed.*/        \
	if(_c == _seq->a){/*_c is the first node.*/                        \
		_seq->a = _c->b;                                               \
	}else{/*_c is not the first node.*/                                \
		_c->a->b = _c->b;                                              \
	}                                                                  \
	if(_c == _seq->b){/*_c is the last node.*/                         \
		_seq->b = _c->a;                                               \
	}else{/*_c is not the last node.*/                                 \
		_c->b->a = _c->a;                                              \
	}                                                                  \
	--_seq->n;                                                         \
})//END __HAC_SEQ_REMOVE

#define /*void*/__HAC_SEQ_INSERTL(base_t, /*HAC_SEQ_T**/_seq, /*__HAC_SEQ_NODE_T**/_a, /*__HAC_SEQ_NODE_T**/_c) ({\
	/*since we are inserting to the left, the node on the right exists.*/\
	if(_a == _seq->a){/*_a is the first node.*/                        \
		_seq->a = _c;                                                  \
	}else{/*_a is not the first node.*/                                \
		_a->a->b = _c;                                                 \
	}                                                                  \
	_c->a = _a->a;                                                     \
	_c->b = _a;                                                        \
	_a->a = _c;                                                        \
	++_seq->n;                                                         \
})//END __HAC_SEQ_INSERTL

#define /*void*/__HAC_SEQ_ISTEP(base_t, /*HAC_SEQ_T**/_seq, /*HAC_SEQ_T*/_sorted, comp) ({\
	__HAC_SEQ_NODE_T(base_t) *_c;                                      \
	base_t e1, e2;                                                     \
	_c = _sorted.b->b;                                                 \
	e1 = _c->v;                                                        \
	while(1){                                                          \
		if(({e2 = _sorted.a->v; comp;}) < 0){                          \
			__HAC_SEQ_REMOVE(base_t, _seq, _c);                        \
			__HAC_SEQ_INSERTL(base_t, _seq, _sorted.a, _c);            \
			break;                                                     \
		}                                                              \
		if(_sorted.a == _sorted.b){                                    \
			_sorted.b = _sorted.b->b;                                  \
			break;                                                     \
		}                                                              \
		_sorted.a = _sorted.a->b;                                      \
	}                                                                  \
	_sorted.a = _seq->a;                                               \
})

/*TODO: In quite some time, once I've implemented iterators and zippers, I may rewrite this using zippers.*/
#define /*void*/__HAC_SEQ_ISORT(base_t, /*HAC_SEQ_T**/seq, comp) ({    \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	for(HAC_SEQ_T(base_t) _sorted = {.a = _seq->a, .b = _seq->a, .n = 1}; _sorted.n < _seq->n; ++_sorted.n){\
		__HAC_SEQ_ISTEP(base_t, _seq, _sorted, comp);                  \
	}                                                                  \
})

/**
 * @brief Sorts a sequence.
 * Uses insertion sort.
 * @param base_t the base type.
 * @param seq a pointer to the sequence to sort.
 * @param comp an expression containing e1 and e2 (the elements to be compared).  Should evaluate < 0 if e1 < e2, > 0 if e1 > e2, and == 0 if e1 == e2.  Remember that just using - will sometimes cause overflow.
 */
#define HAC_SEQ_SORT(base_t, seq, comp) __HAC_SEQ_ISORT(base_t, seq, comp)//TODO: add mergesort.


/**@file _hac_seq_sortable.h*/
/*TODO: In quite some time, once I've implemented iterators and zippers, I may rewrite this using zippers.*/
#define /*void*/__HAC_SEQ_ISORT(base_t, /*HAC_SEQ_T**/seq, comp) ({    \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	HAC_SEQ_T(base_t) _sorted = {.a = _seq->a, .b = _seq->a, .n = 1};  \
	__HAC_SEQ_NODE_T(base_t) *_c;                                      \
	base_t e1, e2;                                                     \
	while(_sorted.n < _seq->n){                                        \
		e1 = _sorted.b->b->v;                                          \
		do{                                                            \
			_c = _sorted.b->b;                                         \
			if(({e2 = _sorted.a->v; comp;}) < 0){                      \
				if(_sorted.a == _seq->a){                              \
					if(_sorted.b->b == _seq->b){/*move the last element to the front*/\
						/*remove _c*/                                  \
						_c->a->b = _c->b;                              \
						_seq->b = _sorted.b;                           \
						/*insert _c*/                                  \
						_c->a = _sorted.a->a;                          \
						_c->b = _sorted.a;                             \
						_c->b->a = _c;                                 \
						_seq->a = _c;                                  \
					}else{/*move a middle element to the front*/       \
						/*remove _c*/                                  \
						_c->a->b = _c->b;                              \
						_c->b->a = _c->a;                              \
						/*insert _c*/                                  \
						_c->a = _sorted.a->a;                          \
						_c->b = _sorted.a;                             \
						_c->b->a = _c;                                 \
						_seq->a = _c;                                  \
					}                                                  \
				}else{                                                 \
					if(_sorted.b->b == _seq->b){/*move the last element to the middle*/\
						/*remove _c*/                                  \
						_c->a->b = _c->b;                              \
						_seq->b = _sorted.b;                           \
						/*insert _c*/                                  \
						_c->a = _sorted.a->a;                          \
						_c->b = _sorted.a;                             \
						_c->b->a = _c;                                 \
						_c->a->b = _c;                                 \
					}else{/*move a middle element to the middle*/      \
						/*remove _c*/                                  \
						_c->a->b = _c->b;                              \
						_c->b->a = _c->a;                              \
						/*insert _c*/                                  \
						_c->a = _sorted.a->a;                          \
						_c->b = _sorted.a;                             \
						_c->b->a = _c;                                 \
						_c->a->b = _c;                                 \
					}                                                  \
				}                                                      \
				break;                                                 \
			}                                                          \
			_sorted.a = _sorted.a->b;                                  \
		}while(_sorted.a != _sorted.b);                                \
		_sorted.a = _seq->a;                                           \
		_sorted.b = _sorted.b->b;                                      \
		++_sorted.n;                                                   \
	}                                                                  \
})

/**
 * @brief Sorts a sequence.
 * Uses insertion sort.
 * @param base_t the base type.
 * @param seq a pointer to the sequence to sort
 * @param comp an expression containing e1 and e2 (the elements to be compared).  Should evaluate < 0 if e1 < e2, > 0 if e1 > e2, and == 0 if e1 == e2.  Remember that just using - will sometimes cause overflow.
 */
#define HAC_SEQ_SORT(base_t, seq, comp) __HAC_SEQ_ISORT(base_t, seq, comp)//TODO: add mergesort.


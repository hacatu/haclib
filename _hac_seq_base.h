//_hac_seq_base.h
#define /*void*/HAC_SEQ_DELETE(base_t, /*HAC_SEQ_T**/seq) ({           \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	for(__HAC_SEQ_NODE_T(base_t) *_cur = _seq->a, *_next; _cur;){      \
		_next = _cur->b;                                               \
		free(_cur);                                                    \
		_cur = _next;                                                  \
	}                                                                  \
	*_seq = HAC_SEQ_EMPTY(base_t);                                     \
	returnvoid;                                                        \
})//END HAC_SEQ_DELETE
#define /*HAC_SEQ_T*/HAC_SEQ_COPY(base_t, /*HAC_SEQ_T**/seq) ({        \
	HAC_SEQ_T(base_t) *_seq = (seq), _ret;                             \
	if(_seq->n){                                                       \
		_ret = HAC_SEQ_NEW(base_t, _seq->a->v);                        \
		for(__HAC_SEQ_NODE_T(base_t) *_node = _seq->a->b; _node; _node = _node->b){\
			if(!__HAC_SEQ_PUSHR_NN(base_t, &_ret, _node->v)){          \
				HAC_SEQ_DELETE(base_t, &_ret);                         \
				break;                                                 \
			}                                                          \
		}                                                              \
		if(_ret.a){                                                    \
			_ret.n = _seq->n;                                          \
		}                                                              \
	}else{                                                             \
		_ret = HAC_SEQ_EMPTY(base_t);                                  \
	}                                                                  \
	_ret;                                                              \
})//END HAC_SEQ_COPY
#define /*HAC_SEQ_T*/HAC_SEQ_FROM(base_t, /*size_t*/size, /*base_t**/array) ({\
	size_t _m = (size);                                                \
	base_t *_a;                                                        \
	HAC_SEQ_T(base_t) _ret = HAC_SEQ_EMPTY(base_t);                    \
	for(size_t _i = 0; _i < _m; ++i){                                  \
		if(!__HAC_SEQ_PUSHR_NN(base_t, &_ret, _a[_i])){                \
			HAC_SEQ_DELETE(base_t, &_ret);                             \
			break;                                                     \
		}                                                              \
	}                                                                  \
	if(_ret.a){                                                        \
		_ret.n = _m;                                                   \
	}                                                                  \
	_ret;                                                              \
})//END HAC_SEQ_FROM


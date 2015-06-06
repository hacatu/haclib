//hac_seq.h
#ifndef __HAC_SEQ__
#define __HAC_SEQ__

#include <stdlib.h>
#include <string.h>
#include "hac_util.h"
#include "hac_pair.h"

#define HAC_SEQ_T(base_t) __HAC_SEQ_##base_t##_T
#define __HAC_SEQ_NODE_T(base_t) struct __HAC_SEQ_NODE_##base_t##_T

#define HAC_SEQ_T_NEW(base_t)                                          \
	__HAC_SEQ_NODE_T(base_t){base_t v; __HAC_SEQ_NODE_T(base_t) *a, *b;};\
	typedef struct{HAC_SEQ_NODE_T(base_t) *a, *b; size_t n;} HAC_SEQ_T(base_t)

#define /*HAC_SEQ_T*/HAC_SEQ_EMPTY(base_t) ((HAC_SEQ_T(base_t)){0})
#define /*HAC_SEQ_T*/__HAC_SEQ_NEW(base_t, /*base_t*/_v) ({            \
	__HAC_SEQ_NODE_T(base_t) *_node = malloc(1*sizeof(__HAC_SEQ_NODE_T(base_t)));\
	_node ?                                                            \
		(HAC_SEQ_T(base_t)){.a = _node, .b = _node, .n = 1}            \
	:                                                                  \
		(HAC_SEQ_T(base_t)){0};                                        \
})//END __HAC_SEQ_NEW
#define /*HAC_SEQ_T*/HAC_SEQ_NEW(base_t, /*base_t*/val) ({             \
	base_t _v = (val);                                                 \
	__HAC_SEQ_NEW(base_t, _v);                                         \
})//END HAC_SEQ_NEW
#define /*int*/__HAC_SEQ_PUSHR_NN(base_t, /*HAC_SEQ_T**/seq, /*base_t*/val) ({\
	int _r = 0;                                                        \
	if((seq)->n){                                                      \
		(seq)->b->b = malloc(1*sizeof(__HAC_SEQ_NODE_T(base_t)));      \
		if((seq)->b->b){                                               \
			*(seq)->b->b = (__HAC_SEQ_NODE_T(base_t)){.a = (seq)->b, .v = (val)};\
			(seq)->b = (seq)->b->b;                                    \
			_r = 1;                                                    \
		}                                                              \
	}else{                                                             \
		*(seq) = HAC_SEQ_NEW(base_t, (val));                           \
		_r = !!(seq)->a;                                               \
	}                                                                  \
	_r;                                                                \
})//END __HAC_SEQ_PUSHR_NN
#define /*int*/HAC_SEQ_PUSHR(base_t, /*HAC_SEQ_T**/seq, /*base_t*/val) ({\
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	if(_seq->n){                                                       \
		_seq->b->b = malloc(1*sizeof(__HAC_SEQ_NODE_T(base_t)));       \
		if(_seq->b->b){                                                \
			*_seq->b->b = (__HAC_SEQ_NODE_T(base_t)){.a = _seq->b, .v = (val)};\
			_seq->b = _seq->b->b;                                      \
			++_seq->n;                                                 \
		}                                                              \
	}else{                                                             \
		*_seq = HAC_SEQ_NEW(base_t, (val));                            \
	}                                                                  \
	!!_seq->n;                                                         \
})//END __HAC_SEQ_PUSHR

#include "_hac_seq_base.h"
#include "_hac_seq_functor.h"
#include "_hac_seq_monoid.h"
#include "_hac_seq_collection.h"
#include "_hac_seq_forward.h"
#include "_hac_seq_reverse.h"
#include "_hac_seq_access.h"
#include "_hac_seq_sortable.h"

#endif


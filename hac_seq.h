/**
 * @file hac_seq.h
 * @brief Doubly linked list data type.
 */
#ifndef __HAC_SEQ__
#define __HAC_SEQ__

#include <stdlib.h>
#include <string.h>
#include "hac_util.h"
#include "hac_pair.h"

#define __HAC_SEQ_T(base_t) __HAC_SEQ_##base_t##_T

/**
 * @brief A macro that represents the type of a sequence of types.
 * Expands to an identifier of the form __HAC_SEQ_##base_t##_T, which has been typedefed by HAC_SEQ_T_NEW(base_t).
 * @param base_t the base type of the sequence, eg double for a sequence of doubles.
 * @return an identifier of the form __HAC_SEQ_##base_t##_T.
 */
#define HAC_SEQ_T(base_t) __HAC_SEQ_T(base_t)

#define __HAC_SEQ_NODE_S(base_t) __HAC_SEQ_NODE_##base_t##_S

#define __HAC_SEQ_NODE_T(base_t) struct __HAC_SEQ_NODE_S(base_t)

/**
 * @brief Sets up the typedef for HAC_SEQ_T(base_t).
 * HAC_SEQ_T(base_t) is typedefed to be a struct with three members: n (the number of nodes), a, and b (pointers to the first and last node).
 * Every node is in turn a struct with three members: v (the element's value), a, and b (pointers to the previous and next nodes).
 * @param base_t the base type.
 */
#define HAC_SEQ_T_NEW(base_t)                                          \
	__HAC_SEQ_NODE_T(base_t){base_t v; __HAC_SEQ_NODE_T(base_t) *a, *b;};\
	typedef struct{__HAC_SEQ_NODE_T(base_t) *a, *b; size_t n;} HAC_SEQ_T(base_t)

/**
 * @brief A macro that expands to an empty sequence of a type.
 * n is 0 and a and b are NULL.
 * @param base_t the base type.
 * @return an empty sequence for base_t.
 */
#define HAC_SEQ_EMPTY(base_t) ((HAC_SEQ_T(base_t)){0})

#define /*HAC_SEQ_T*/__HAC_SEQ_NEW(base_t, /*base_t*/_v) ({            \
	__HAC_SEQ_NODE_T(base_t) *_node = malloc(1*sizeof(__HAC_SEQ_NODE_T(base_t)));\
	_node ?                                                            \
		(*_node = (__HAC_SEQ_NODE_T(base_t)){.v = _v},                 \
		(HAC_SEQ_T(base_t)){.a = _node, .b = _node, .n = 1})           \
	:                                                                  \
		(HAC_SEQ_T(base_t)){0};                                        \
})//END __HAC_SEQ_NEW

/**
 * @brief Creates a sequence with one element.
 * The only element will have a value of val.
 * @param base_t the base type.
 * @param val the value for the element.
 * @return a sequence with one element with the value val.
 */
#define HAC_SEQ_NEW(base_t, val) ({                                    \
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

/**
 * @brief Adds a value onto the right end of a sequence.
 * @param base_t the base type.
 * @param seq a pointer to the sequence to append to.
 * @param val the value to append to the sequence.
 * @return 1 on success, 0 on an allocation failure.
 */
#define HAC_SEQ_PUSHR(base_t, seq, val) ({                             \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	int _ret = 0;                                                      \
	if(_seq->n){                                                       \
		_seq->b->b = malloc(1*sizeof(__HAC_SEQ_NODE_T(base_t)));       \
		if(_seq->b->b){                                                \
			*_seq->b->b = (__HAC_SEQ_NODE_T(base_t)){.a = _seq->b, .v = (val)};\
			_seq->b = _seq->b->b;                                      \
			++_seq->n;                                                 \
			_ret = 1;                                                  \
		}                                                              \
	}else{                                                             \
		*_seq = HAC_SEQ_NEW(base_t, (val));                            \
		_ret = _seq->n;                                                \
	}                                                                  \
	!!_ret;                                                            \
})//END HAC_SEQ_PUSHR

#define /*void*/__HAC_SEQ_FIXP(base_t, /*HAC_SEQ_T**/seq) ({           \
	size_t _i = (seq)->n;                                              \
	__HAC_SEQ_NODE_T(base_t) *_node = (seq)->a;                        \
	while(_i > 0){                                                     \
		_node->b->a = _node;                                           \
		_node = _node->b;                                              \
		--_i;                                                          \
	}                                                                  \
	(seq)->b = _node;                                                  \
	(seq)->a = (seq)->b = NULL;                                        \
})//END __HAC_SEQ_FIXP

#include "_hac_seq_base.h"
#include "_hac_seq_functor.h"
#include "_hac_seq_monoid.h"
#include "_hac_seq_collection.h"
#include "_hac_seq_forward.h"
#include "_hac_seq_reverse.h"
#include "_hac_seq_shuffle.h"
#include "_hac_seq_sortable.h"

#endif


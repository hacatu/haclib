/**@file _hac_seq_shuffle.h*/
#define /*void*/__HAC_SEQ_KSHUFFLE_ARR(base_t, /*base_t**/arr, n, rand) ({\
	base_t _t;                                                         \
	for(size_t _i = (n) - 1, _j; _i; --_i){                            \
		_j = ({rand;})*(_i + 1);                                       \
		_t = arr[_i];                                                  \
		arr[_i] = arr[_j];                                             \
		arr[_j] = _t;                                                  \
	}                                                                  \
})//END __HAC_SEQ_KSHUFFLE_ARR

#define /*void*/__HAC_SEQ_KSHUFFLE(base_t, /*HAC_SEQ_T**/seq, rand) ({ \
	HAC_SEQ_T(base_t) *_seq = (seq);                                   \
	HAC_WITH(base_t *_a, malloc((_seq->n)*sizeof(base_t)), _a, ({      \
		size_t _i = 0;                                                 \
		HAC_SEQ_FOREACH(base_t, _seq, ({                               \
			_a[_i++] = e;                                              \
		}));                                                           \
		__HAC_SEQ_KSHUFFLE_ARR(base_t, /*base_t**/_a, _seq->n, rand);  \
		_i = 0;                                                        \
		HAC_SEQ_FOREACHP(base_t, _seq, ({                              \
			*e = _a[_i++];                                             \
		}));                                                           \
		free(_a);                                                      \
	}));                                                               \
})//END __HAC_SEQ_KSHUFFLE

/**
 * @brief Shuffles a sequence.
 * Turns the sequence into an array and Knuth shuffles it.
 * @param base_t the base type.
 * @param seq a pointer to the sequence to shuffle
 * @param rand an expression that returns a double between [0,1).
 */
#define HAC_SEQ_SHUFFLE(base_t, seq, rand) __HAC_SEQ_KSHUFFLE(base_t, seq, rand)//TODO: make __HAC_SEQ_MSHUFFLE and __HAC_SEQ_ISHUFFLE and find the best.


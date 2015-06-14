/**@file _hac_seq_collection.h*/
/**
 * @brief Creates a sequence with only the elements of a sequence meeting a condition.
 * @param base_t the base type.
 * @param seq a pointer the sequence to copy.
 * @param expr an expression containing e (the current element).  If true, e will be in the output sequence.
 * @return a sequence with only the elements of seq meeting expr.
 */
#define HAC_SEQ_FILTER(base_t, seq, expr) ({                           \
	HAC_SEQ_T(base_t) _ret = HAC_SEQ_EMPTY(base_t);                    \
	HAC_SEQ_FOREACH(base_t, seq, ({                                    \
		if(({expr;})){                                                 \
			HAC_SEQ_PUSHR(base_t, &_ret, e);                           \
		}                                                              \
		returnvoid;                                                    \
	}));                                                               \
	_ret;                                                              \
})//END HAC_VEC_FILTER


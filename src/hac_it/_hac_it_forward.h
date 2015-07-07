/**
 * @file _hac_it_forward.h
 * @brief Iterators.  Yes.
 * Macros:
 *  HAC_IT_T()
 *  HAC_ARR_IT_INIT()
 *  HAC_ARR_IT()
 *  HAC_VEC_IT_INIT()
 *  HAC_VEC_IT()
 *  HAC_SEQ_IT_INIT()
 *  HAC_SEQ_IT()
 *  HAC_CUSTOM_IT()
 *  Forward:
 *   HAC_IT_COPY()
 *   HAC_IT_NEXT()
 *   HAC_IT_V()
 *   HAC_IT_EQ()
 *  Bidirectional:
 *   HAC_IT_PREV()
 *  Random Access:
 *   HAC_IT_NEXT_BY()
 *   HAC_IT_PREV_BY()
 *   HAC_IT_COMP()
 *   HAC_IT_GET()
 */
#define HAC_IT_COPY(it) ({                                             \
	__typeof__(it) _it = (it), _ret = malloc(1*sizeof(it));            \
	if(_ret){                                                          \
		memcpy(_ret, _it, 1*sizeof(it));                               \
	}                                                                  \
	_ret;                                                              \
})//END HAC_IT_COPY

#define HAC_IT_V(it) (*(it)->v)

#define HAC_IT_EQ(ita, itb) ({                                         \
	__typeof__(ita) _a = (ita), _b = (itb);                            \
	_a->ctnr == _b->ctnr && _a->pos == _b->pos;                        \
})//END HAC_IT_EQ

#define HAC_IT_NEXT(it) (*({                                           \
	HAC_AUTO_T(it) _it = (it);                                         \
	__typeof__(it->v) _ret;                                            \
	switch(_it->intr){                                                 \
		case HAC_IT_FORWARD:                                           \
		case HAC_IT_BIDIRECTIONAL:                                     \
		_ret = HAC_O_CALL(_it, next);                                  \
		break;                                                         \
		case HAC_IT_RANDOM_ACCESS:                                     \
		_ret = HAC_O_CALL(_it, nextBy, 1);                             \
		break;                                                         \
	}                                                                  \
	_ret;                                                              \
}))//END HAC_IT_NEXT


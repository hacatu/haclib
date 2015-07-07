/**
 * @file _hac_it_random_access.h
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
#define HAC_IT_NEXT_BY(it, n) (*({                                     \
	HAC_AUTO_T(it) _it = (it);                                         \
	__typeof__((it)->v) _ret;                                          \
	switch(_it->intr){                                                 \
		case HAC_IT_FORWARD:                                           \
		case HAC_IT_BIDIRECTIONAL:                                     \
		_ret = NULL;                                                   \
		break;                                                         \
		case HAC_IT_RANDOM_ACCESS:                                     \
		_ret = HAC_O_CALL(_it, nextBy, n);                             \
		break;                                                         \
	}                                                                  \
	_ret;                                                              \
}))//END HAC_IT_NEXT_BY

#define HAC_IT_PREV_BY(it, n) (*({                                     \
	HAC_AUTO_T(it) _it = (it);                                         \
	__typeof__((it)->v) _ret;                                          \
	switch(_it->intr){                                                 \
		case HAC_IT_FORWARD:                                           \
		case HAC_IT_BIDIRECTIONAL:                                     \
		_ret = NULL;                                                   \
		break;                                                         \
		case HAC_IT_RANDOM_ACCESS:                                     \
		_ret = HAC_O_CALL(_it, nextBy, -n);                            \
		break;                                                         \
	}                                                                  \
	_ret;                                                              \
}))//END HAC_IT_PREV_BY

#define HAC_IT_COMP(ita, itb) ({                                       \
	HAC_AUTO_T(ita), _it = (ita);                                      \
	int _ret;                                                          \
	switch(_it->intr){                                                 \
		case HAC_IT_FORWARD:                                           \
		case HAC_IT_BIDIRECTIONAL:                                     \
		break;                                                         \
		case HAC_IT_RANDOM_ACCESS:                                     \
		_ret = (itb)->pos - _it->pos;                                  \
		break;                                                         \
	}                                                                  \
	_ret;                                                              \
})//END HAC_IT_COMP

#define HAC_IT_GET(it, n) (*({                                         \
	HAC_AUTO_T(it) _it = (it);                                         \
	__typeof__((it)->v) _ret;                                          \
	switch(_it->intr){                                                 \
		case HAC_IT_FORWARD:                                           \
		case HAC_IT_BIDIRECTIONAL:                                     \
		_ret = NULL;                                                   \
		break;                                                         \
		case HAC_IT_RANDOM_ACCESS:                                     \
		_ret = HAC_O_CALL(_it, get, n);                                \
		break;                                                         \
	}                                                                  \
	_ret;                                                              \
}))//END HAC_IT_GET


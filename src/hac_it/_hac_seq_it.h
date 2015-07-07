/**
 * @file _hac_seq_it.h
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
 /**
 * @brief expands to the iterator type for a sequence with base type base_t, of the form __HAC_SEQ_##base_t##_T##I.
 * This identifier should be typedefed by HAC_SEQ_IT_INIT().  This might be
 * used like HAC_SEQ_IT_T(int), which is in fact equivalent to HAC_IT_T(HAC_SEQ_T(int)).
 * @param base_t the base type.
 */
#define HAC_SEQ_IT_T(base_t) HAC_IT_T(HAC_SEQ_T(base_t))

/**
 * @brief set up the proper typedefs and function definitions for a sequence iterator of base type base_t.
 * The names __HAC_SEQ_##base_t##_T##I, __HAC_SEQ_##base_t##_T##I##_next, and __HAC_SEQ_##base_t##_T##I##_prev
 * are defined.
 * @param base_t the base type.
 */
#define HAC_SEQ_IT_INIT(base_t)                                        \
	typedef struct HAC_SEQ_IT_T(base_t) HAC_SEQ_IT_T(base_t);          \
	struct HAC_SEQ_IT_T(base_t){                                       \
		HAC_IT_INTERFACE intr;                                         \
		base_t *v;                                                     \
		HAC_SEQ_T(base_t) *ctnr;                                       \
		__HAC_SEQ_NODE_T(base_t) *pos;                                 \
		base_t *(*next)(HAC_SEQ_IT_T(base_t)*);                        \
		base_t *(*prev)(HAC_SEQ_IT_T(base_t)*);                        \
	};                                                                 \
	base_t *HAC_PASTE(HAC_SEQ_IT_T(base_t), _next)(HAC_SEQ_IT_T(base_t) *self){\
		self->pos = self->pos->b;                                      \
		return self->v = &self->pos->v;                                \
	}                                                                  \
	base_t *HAC_PASTE(HAC_SEQ_IT_T(base_t), _prev)(HAC_SEQ_IT_T(base_t) *self){\
		self->pos = self->pos->a;                                      \
		return self->v = &self->pos->v;                                \
	}

/**
 * @brief creates a bidirectional iterator for a sequence.
 */
#define HAC_SEQ_IT(base_t, seq) ({                                     \
	HAC_AUTO_T(seq) _seq = (seq);                                      \
	(HAC_SEQ_IT_T(base_t)){                                            \
		.intr = HAC_IT_BIDIRECTIONAL,                                  \
		.v = _seq->a,                                                  \
		.ctnr = _seq,                                                  \
		.pos = _seq->a,                                                \
		.next = HAC_PASTE(HAC_SEQ_IT_T(base_t), _next),                \
		.prev = HAC_PASTE(HAC_SEQ_IT_T(base_t), _prev)                 \
	};                                                                 \
})//END HAC_SEQ_IT
	

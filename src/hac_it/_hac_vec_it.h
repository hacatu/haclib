/**
 * @file _hac_vec_it.h
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
 * @brief expands to the iterator type for a vector with base type base_t, of the form __HAC_VEC_##base_t##_T##I.
 * This identifier should be typedefed by HAC_VEC_IT_INIT().  This might be
 * used like HAC_VEC_IT_T(int), which is in fact equivalent to HAC_IT_T(HAC_VEC_T(int)).
 * @param base_t the base type.
 */
#define HAC_VEC_IT_T(base_t) HAC_IT_T(HAC_VEC_T(base_t))

/**
 * @brief set up the proper typedefs and function definitions for a vector iterator of base type base_t.
 * The names __HAC_VEC_##base_t##_T##I, __HAC_VEC_##base_t##_T##I##_nextBy, and __HAC_VEC_##base_t##_T##I##_get
 * are defined.
 * @param base_t the base type.
 */
#define HAC_VEC_IT_INIT(base_t)                                        \
	typedef struct HAC_VEC_IT_T(base_t) HAC_VEC_IT_T(base_t);          \
	struct HAC_VEC_IT_T(base_t){                                       \
		HAC_IT_INTERFACE intr;                                         \
		base_t *v;                                                     \
		HAC_VEC_T(base_t) *ctnr;                                       \
		size_t pos;                                                    \
		base_t *(*nextBy)(HAC_VEC_IT_T(base_t)*, ptrdiff_t n);         \
		base_t *(*get)(HAC_VEC_IT_T(base_t)*, ptrdiff_t n);            \
	};                                                                 \
	base_t *HAC_PASTE(HAC_VEC_IT_T(base_t), _nextBy)(HAC_VEC_IT_T(base_t) *self, ptrdiff_t n){\
		self->pos += n;                                                \
		return self->v = self->ctnr->a + self->pos;                    \
	}                                                                  \
	base_t *HAC_PASTE(HAC_VEC_IT_T(base_t), _get)(HAC_VEC_IT_T(base_t) *self, ptrdiff_t n){\
		return self->ctnr->a + self->pos + n;                          \
	}

/**
 * @brief creates a random access iterator for a vector.
 */
#define HAC_VEC_IT(base_t, vec) ({                                     \
	HAC_AUTO_T(vec) _vec = (vec);                                      \
	(HAC_VEC_IT_T(base_t)){                                            \
		.intr = HAC_IT_RANDOM_ACCESS,                                  \
		.v = _vec->a,                                                  \
		.ctnr = _vec,                                                  \
		.pos = 0,                                                      \
		.nextBy = HAC_PASTE(HAC_VEC_IT_T(base_t), _nextBy),            \
		.get = HAC_PASTE(HAC_VEC_IT_T(base_t), _get)                   \
	};                                                                 \
})//END HAC_VEC_IT
	

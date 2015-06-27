/**
 * @file hac_pair.h
 * @brief Homogenous pair data type.
 */
#ifndef __HAC_PAIR__
#define __HAC_PAIR__

#include "hac_util.h"

#define __HAC_PAIR_T(base_t) __HAC_PAIR_##base_t##_T

/**
 * @brief A macro that represents the type of a pair of base_t values.
 * Expands to an identifier of the form __HAC_PAIR_##base_t##_T, which has been typedefed by HAC_PAIR_T_NEW(base_t).
 * @param base_t the base type of the pair, eg double for a pair of doubles.
 * @return an identifier of the form __HAC_PAIR_##base_t##_T.
 */
#define HAC_PAIR_T(base_t) __HAC_PAIR_T(base_t)

/**
 * @brief Sets up the typedef for HAC_PAIR_T(base_t).
 * HAC_PAIR_T(base_t) is typedefed to be a struct with two members of type base_t: a and b.
 * @param base_t the base type.
 */
#define HAC_PAIR_T_NEW(base_t) typedef struct{base_t a, b;} HAC_PAIR_T(base_t)

/**
 * @brief Makes a pair from two values.
 * @param base_t the base type.
 * @param _a a base_t value for the first element of the pair.
 * @param _b a base_t value for the second element of the pair.
 * @return a pair of _a and _b.
 */
#define HAC_PAIR_MAKE(base_t, _a, _b) ((HAC_PAIR_T(base_t)){.a = _a, .b = _b})

/**
 * @brief Swaps the two elements of a pair.
 * Modifies the pair but also returns it.
 * @param base_t the base type.
 * @param pair a pointer to the pair whose elements to swap.
 * @return a pointer to the pair whose elements were swapped.
 */
#define HAC_PAIR_SWAP(base_t, pair) ({                                 \
	HAC_PAIR_T(base_t) *_p = (pair);                                   \
	base_t _t = _p->a;                                                 \
	_p->a = _p->b;                                                     \
	_p->b = _t;                                                        \
	_p;                                                                \
})//END HAC_PAIR_SWAP

/**
 * @brief Creates a copy of a pair.
 * Does not deep copy each element in any way.
 * @param base_t the base type.
 * @param pair a pointer to the pair to copy.
 * @return a new pair which is a copy of pair.
 */
#define HAC_PAIR_COPY(base_t, pair) ({                                 \
	HAC_PAIR_T(base_t) *_p = (pair);                                   \
	HAC_PAIR_MAKE(base_t, _p->a, _p->b);                               \
})//END HAC_PAIR_COPY

#endif


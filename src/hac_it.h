/**
 * @file hac_it.h
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
#ifndef __HAC_IT__
#define __HAC_IT__

#include <stdlib.h>
#include <string.h>
#include "hac_obj.h"

#define __HAC_IT_T(ctnr_t) ctnr_t##I

/**
 * @brief expands to the iterator type for a container type ctnr_t, of the form ctnr_t##I.
 * This identifier should be typedefed by HAC_<containter kind>_IT_INIT().  This might be
 * used like HAC_IT_T(HAC_VEC_T(int)), which is in fact equivalent to HAC_VEC_IT_T(int).
 * @param ctnr_t the container type.
 */
#define HAC_IT_T(ctnr_t) __HAC_IT_T(ctnr_t)

/**
 * @brief the interface supported by an iterator.
 * Currently, there is no support for insertion or deletion by iterators of any interface.
 * Further, attempting to use an unsupported macro on an iteratior (like HAC_IT_GET(HAC_IT_FORWARD, 3)),
 * is an error and the macros may dereferance null or return uninitialized values or similar.
 */
typedef enum{HAC_IT_FORWARD, HAC_IT_BIDIRECTIONAL, HAC_IT_RANDOM_ACCESS} HAC_IT_INTERFACE;

/**Iterators are pointers to structs which have at least these fields:
 * struct it{
 *     HAC_IT_INTERFACE intr;
 *     base_t *v;
 *     <ctnr>_t *ctnr;
 *     <?> pos;
 *     union{//If you access any of these fields directly... well, just don't do that.
 *         struct{//HAC_IT_FORWARD
 *             base_t *(*next)(struct it*);
 *         };
 *         struct{//HAC_IT_BIDIRECTIONAL
 *             base_t *(*next)(struct it*);
 *             base_t *(*prev)(struct it*);
 *         };
 *         struct{//HAC_IT_RANDOM_ACCESS
 *             base_t *(*nextBy)(struct it*, offset_t);
 *             base_t *(*get)(struct it*, offset_t);
 *         };
 *     };
 * };
 * 
 */

#include "hac_it/_hac_it_forward.h"
#include "hac_it/_hac_it_bidirectional.h"
#include "hac_it/_hac_it_random_access.h"

#ifdef __HAC_VEC__
#include "hac_it/_hac_vec_it.h"
#endif

#ifdef __HAC_SEQ__
#include "hac_it/_hac_seq_it.h"
#endif

#endif


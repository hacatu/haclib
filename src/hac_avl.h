/**
 * @file hac_avl.h
 * @brief avl trees.
 */
#ifndef __HAC_AVL__
#define __HAC_AVL__

#include <stdlib.h>
#include <string.h>
#include "hac_util.h"

#define __HAC_AVL_T(base_t) __HAC_AVL_##base_t##_T

/**
 * @brief A macro that represents the type of an avl tree of types.
 * Expands to an identifier of the form __HAC_AVL_##base_t##_T, which has been typedefed by HAC_AVL_T_NEW(base_t).
 * @param base_t the base type of the avl tree, eg double for an avl tree of doubles.
 * @return an identifier of the form __HAC_AVL_##base_t##_T.
 */
#define HAC_AVL_T(base_t) __HAC_AVL_T(base_t)

#define __HAC_AVL_NODE_S(base_t) __HAC_AVL_NODE_##base_t##_S

#define __HAC_AVL_NODE_T(base_t) struct __HAC_AVL_NODE_S(base_t)

/**
 * @brief Sets up the typedef for HAC_AVL_T(base_t).
 * HAC_AVL_T(base_t) is typedefed to be a struct with one member: r (a pointer to the root node).
 * Every node is in turn a struct with five members: v (the element's value), k (the node's balance factor), a, b, and p (pointers to the previous, next, and parent nodes).
 * @param base_t the base type.
 */
#define HAC_AVL_T_NEW(base_t)                                          \
	__HAC_AVL_NODE_T(base_t){base_t v; int k; __HAC_AVL_NODE_T(base_t) *a, *b, *p;};\
	typedef struct{__HAC_AVL_NODE_T(base_t) *r;} HAC_AVL_T(base_t)

/**
 * @brief A macro that expands to an empty avl tree of a type.
 * r is NULL.
 * @param base_t the base type.
 * @return an empty avl tree for base_t.
 */
#define HAC_AVL_EMPTY(base_t) ((HAC_AVL_T(base_t)){0})

#define /*HAC_AVL_T*/__HAC_AVL_NEW(base_t, /*base_t*/_v) ({            \
	__HAC_AVL_NODE_T(base_t) *_node = malloc(1*sizeof(__HAC_AVL_NODE_T(base_t)));\
	_node ?                                                            \
		(*_node = (__HAC_AVL_NODE_T(base_t)){.v = _v},                 \
		(HAC_AVL_T(base_t)){.r = _node})                               \
	:                                                                  \
		(HAC_AVL_T(base_t)){0};                                        \
})//END __HAC_AVL_NEW

/**
 * @brief Creates an avl tree with one element.
 * The only element will have a value of val.
 * @param base_t the base type.
 * @param val the value for the element.
 * @return an avl tree with one element with the value val.
 */
#define HAC_AVL_NEW(base_t, val) ({                                    \
	base_t _v = (val);                                                 \
	__HAC_AVL_NEW(base_t, _v);                                         \
})//END HAC_AVL_NEW

#include "hac_avl/_hac_avl_get.h"
#include "hac_avl/_hac_avl___traversal.h"
#include "hac_avl/_hac_avl_rotation.h"
#include "hac_avl/_hac_avl_insert.h"
#include "hac_avl/_hac_avl_remove.h"
#include "hac_avl/_hac_avl_base.h"

#endif


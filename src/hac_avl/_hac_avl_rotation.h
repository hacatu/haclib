/**@file _hac_avl_rotation.h*/

/*
 *     Q           P
 *    / \  Right  / \
 *   P   C  -->  A   Q
 *  / \     <--     / \
 * A   B   Left    B   C
 */
/*Assumes P exists.*/
#define __HAC_AVL_ROTATER(base_t, q) ({                                \
	__HAC_AVL_NODE_T(base_t) *_p = q->a, *_b = _p->b;                  \
	if(q->p){                                                          \
		if(q == q->p->a){                                              \
			q->p->a = _p;                                              \
		}else{                                                         \
			q->p->b = _p;                                              \
		}                                                              \
	}                                                                  \
	_p->b = q;                                                         \
	q->a = _b;                                                         \
	_p;                                                                \
})//END __HAC_AVL_ROTATER

/*Assumes Q exists.*/
#define __HAC_AVL_ROTATEL(base_t, p) ({                                \
	__HAC_AVL_NODE_T(base_t) *_q = p->a, *_b = _q->a;                  \
	if(p->p){                                                          \
		if(p == p->p->a){                                              \
			p->p->a = _q;                                              \
		}else{                                                         \
			p->p->b = _q;                                              \
		}                                                              \
	}                                                                  \
	_q->a = p;                                                         \
	p->b = _b;                                                         \
	_q;                                                                \
})//END __HAC_AVL_ROTATEL


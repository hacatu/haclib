/**@file _hac_avl_rotation.h*/
/*
 *     Q           P
 *    / \  Right  / \
 *   P   C  -->  A   Q
 *  / \     <--     / \
 * A   B   Left    B   C
 */
/*Assumes P exists.*/
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_ROTATER(base_t, /*__HAC_AVL_NODE_T**/nq) ({\
	__HAC_AVL_NODE_T(base_t) *_q = (nq), *_p = _q->a, *_b = _p->b;     \
	if(_q->p){                                                         \
		if(_q == _q->p->a){                                            \
			_q->p->a = _p;                                             \
		}else{                                                         \
			_q->p->b = _p;                                             \
		}                                                              \
	}                                                                  \
	_p->b = _q;                                                        \
	_q->a = _b;                                                        \
	_p->p = _q->p;                                                     \
	_q->p = _p;                                                        \
	--_q->k;                                                           \
	if(_p->k > 0){/*a is longer than b*/                               \
		_q->k -= _p->k;                                                \
	}                                                                  \
	--_p->k;/*NOTE: this assumes q->k started > -2 (if q->k == -2, rotatel would be used*/\
	_p;                                                                \
})//END __HAC_AVL_ROTATER

/*Assumes Q exists.*/
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_ROTATEL(base_t, /*__HAC_AVL_NODE_T**/np) ({\
	__HAC_AVL_NODE_T(base_t) *_p = (np), *_q = _p->b, *_b = _q->a;     \
	if(_p->p){                                                         \
		if(_p == _p->p->a){                                            \
			_p->p->a = _q;                                             \
		}else{                                                         \
			_p->p->b = _q;                                             \
		}                                                              \
	}                                                                  \
	_q->a = _p;                                                        \
	_p->b = _b;                                                        \
	_q->p = _p->p;                                                     \
	_p->p = _q;                                                        \
	++_p->k;                                                           \
	if(_q->k < 0){/*c is longer than b*/                               \
		_p->k -= _q->k;                                                \
	}                                                                  \
	++_q->k;/*NOTE: this assumes q->k started < 2 (if q->k == 2, rotater would be used*/\
	_q;                                                                \
})//END __HAC_AVL_ROTATEL


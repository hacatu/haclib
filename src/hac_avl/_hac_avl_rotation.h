/**@file _hac_avl_rotation.h*/
/*
 *     Q           P
 *    / \  Right  / \
 *   P   C  -->  A   Q
 *  / \     <--     / \
 * A   B   Left    B   C
 */
/*Assumes P exists.*/
/*returns root node*/
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_ROTATER(base_t, /*__HAC_AVL_NODE_T**/nq) ({\
	__HAC_AVL_NODE_T(base_t) *_q = (nq), *_p = _q->a, *_b = _p->b;     \
	int _dk;                                                           \
	if(_q->p){                                                         \
		if(_q == _q->p->a){                                            \
			_q->p->a = _p;                                             \
		}else{                                                         \
			_q->p->b = _p;                                             \
		}                                                              \
	}                                                                  \
	_p->b = _q;                                                        \
	_q->a = _b;                                                        \
	if(_b){                                                            \
		_b->p = _q;                                                    \
	}                                                                  \
	_p->p = _q->p;                                                     \
	_q->p = _p;                                                        \
	_dk = __HAC_AVL_ROTATER_K(_q->k, _p->k);                           \
	__HAC_AVL_FIXK(base_t, _p, _dk);                                   \
})//END __HAC_AVL_ROTATER

/*Assumes Q exists.*/
/*returns root node*/
#define /*__HAC_AVL_NODE_T**/__HAC_AVL_ROTATEL(base_t, /*__HAC_AVL_NODE_T**/np) ({\
	__HAC_AVL_NODE_T(base_t) *_p = (np), *_q = _p->b, *_b = _q->a;     \
	int _dk;                                                           \
	if(_p->p){                                                         \
		if(_p == _p->p->a){                                            \
			_p->p->a = _q;                                             \
		}else{                                                         \
			_p->p->b = _q;                                             \
		}                                                              \
	}                                                                  \
	_q->a = _p;                                                        \
	_p->b = _b;                                                        \
	if(_b){                                                            \
		_b->p = _p;                                                    \
	}                                                                  \
	_q->p = _p->p;                                                     \
	_p->p = _q;                                                        \
	_dk = __HAC_AVL_ROTATEL_K(_p->k, _q->k);                           \
	__HAC_AVL_FIXK(base_t, _q, _dk);                                   \
})//END __HAC_AVL_ROTATEL


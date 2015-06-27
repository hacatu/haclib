/**@file _hac_avl_rotation_k.h*/
/*   N       N
 *  / \     / \
 * A   B  A+d  B
 * K0 = A - B, H0 = max(A, B) + 1
 * K1 = A + d - B, H1 = max(A + d, B) + 1
 * 
 * H1 - H0 = max(A + d, B) - max(A, B)
 * H1 - H0 = max(A + d - B, 0) + B - (max(A - B, 0) + B)
 * H1 - H0 = max(K1, 0) - max(K0, 0)
 */
#define __HAC_AVL_DHA(k, dh) ({                                        \
	k += dh;                                                           \
	dh = HAC_MAX(k, 0) - HAC_MAX(k - dh, 0);                           \
})//END __HAC_AVL_DHA

/*
 *   N      N
 *  / \    / \
 * A   B  A  B+d
 * K0 = A - B, H0 = max(A, B) + 1
 * K1 = A - (B + d), H1 = max(A, B + d) + 1
 * 
 * H1 - H0 = max(A, B + d) - max(A, B)
 * H1 - H0 = max(A - (B + d), 0) + B + d - (max(A - B, 0) + B)
 * H1 - H0 = max(K1, 0) + d - max(K0, 0)
 */
#define __HAC_AVL_DHB(k, dh) ({                                        \
	k -= dh;                                                           \
	dh = HAC_MAX(k, 0) - HAC_MAX(k + dh, 0) + dh;                      \
})//END __HAC_AVL_DHB

#define /*__HAC_AVL_NODE_T**/__HAC_AVL_FIXK(base_t, /*__HAC_AVL_NODE_T**/n, /*int*/ dh) ({\
	int _dh = (dh);                                                    \
	while(n->p){                                                       \
		if(n == n->p->a){                                              \
			__HAC_AVL_DHA(n->p->k, _dh);                               \
		}else{                                                         \
			__HAC_AVL_DHB(n->p->k, _dh);                               \
		}                                                              \
		n = n->p;                                                      \
	}                                                                  \
	n;                                                                 \
})//END __HAC_AVL_ROTATE_FIXK

/*     Q           P
 *    / \  Right  / \
 *   P   C  -->  A   Q
 *  / \     <--     / \
 * A   B   Left    B   C
 */
/* Pl = A - B, Ql = max(A, B) + 1 - C
 *             Ql = max(A - B, 0) + B + 1 - C
 *             Ql = max(Pl, 0) + 1 + B - C
 *             Ql - 1 - max(Pl, 0) = B - C
 * 
 * Qr = B - C, Pr = A - (max(B, C) + 1)
 *             Pr = A - (B + max(0, C - B) + 1)
 *             Pr = A - B - 1 - max(-Qr, 0)
 *             Pr = Pl - 1 - max(-Qr, 0)
 * 
 * Qr = Ql - 1 - max(Pl, 0)
 * Qr + 1 + max(Pl, 0) = Ql
 * 
 * Pr = Pl - 1 - max(-Qr, 0)
 * max(-Qr, 0) = Pl - Pr - 1
 * Pl = Pr + 1 + max(-Qr, 0)
 * 
 * Hl = 1 + max(1 + max(A, B), C)
 * Hr = 1 + max(A, 1 + max(B, C))
 * Hr - Hl = max(A, 1 + max(B, C)) - max(1 + max(A, B), C)
 * Hr - Hl = max(A - B, 1 + max(0, C - B)) + B - (max(1 + max(A - B, 0), C - B) + B)
 * Hr - Hl = max(Pl, 1 + max(-Qr, 0)) - max(1 + max(Pl, 0), -Qr)
 * Hr - Hl = max(Pl - 1 - max(-Qr, 0), 0) + 1 + max(-Qr, 0) - (max(Qr + 1 + max(Pl, 0), 0) - Qr)
 * Hr - Hl = max(Pr, 0) + 1 + max(-Qr, 0) - max(Ql, 0) + Qr
 * Hr - Hl = max(Pr, 0) + 1 + Pl - Pr - 1 - max(Ql, 0) + Qr
 * Hr - Hl = max(-Pr, 0) - max(Ql, 0) + Qr + Pl
 */
#define __HAC_AVL_DHR(ql, pl, qr, pr) ((pr < 0 ? -pr : 0) - (ql > 0 ? ql : 0) + qr + pl)
#define __HAC_AVL_DHL(pr, qr, pl, ql) ((ql > 0 ? ql : 0) + (pr < 0 ? pr : 0) - qr - pl)
 
 #define /*int*/__HAC_AVL_ROTATER_K(/*int*/qk, /*int*/pk) ({           \
	int _ql = (qk), _pl = (pk), _qr, _pr;                              \
	_qr = _ql - 1;                                                     \
	if(_pl > 0){                                                       \
		_qr -= _pl;                                                    \
	}                                                                  \
	_pr = _pl - 1;                                                     \
	if(_qr < 0){                                                       \
		_pr += _qr;                                                    \
	}                                                                  \
	qk = _qr;                                                          \
	pk = _pr;                                                          \
	__HAC_AVL_DHR(_ql, _pl, _qr, _pr);                                 \
})//END __HAC_AVL_ROTATER_K

#define /*int*/__HAC_AVL_ROTATEL_K(/*int*/pk, /*int*/qk) ({            \
	int _pr = (pk), _qr = (qk), _pl, _ql;                              \
	_pl = _pr + 1;                                                     \
	if(_qr < 0){                                                       \
		_pl -= _qr;                                                    \
	}                                                                  \
	_ql = _qr + 1;                                                     \
	if(_pl > 0){                                                       \
		_ql += _pl;                                                    \
	}                                                                  \
	pk = _pl;                                                          \
	qk = _ql;                                                          \
	__HAC_AVL_DHL(_pr, _qr, _pl, _ql);                                 \
})//END __HAC_AVL_ROTATEL_K


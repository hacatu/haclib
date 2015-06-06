/**@file _hac_vec_sortable.h*/
#define /*size_t*/__HAC_VEC_AMAX(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp) ({\
	size_t _amax = i1;                                                 \
	base_t _max = vec->a[i1], e1, e2;                                  \
	for(size_t _i = i1 + 1; _i < i2; ++_i){                            \
		e1 = _max;                                                     \
		e2 = vec->a[_i];                                               \
		if(({comp;}) > 0){                                             \
			_max = vec->a[_i];                                         \
			_amax = _i;                                                \
		}                                                              \
	}                                                                  \
	_amax;                                                             \
})//END __HAC_VEC_AMAX

#define /*void*/__HAC_VEC_SSTEP(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp, swap) ({\
	HAC_VEC_T(base_t) *v = vec;                                        \
	size_t j = __HAC_VEC_AMAX(base_t, vec, i1, i2, comp), i = i1;      \
	({swap;});                                                         \
	returnvoid;                                                        \
})//END __HAC_VEC_SSTEP

#define /*void*/__HAC_VEC_SSORT(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp, swap) ({\
	for(size_t _i = i1; _i < i2; ++_i){                                \
		__HAC_VEC_SSTEP(base_t, vec, _i, i2, comp, swap);              \
	}                                                                  \
})//END __HAC_VEC_SSORT

#define /*base_t*/__HAC_VEC_PIVOT(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp) ({\
	size_t _mi = (i1 + i2)/2;                                          \
	base_t _a = vec->a[i1], _b = vec->a[i2 - 1], _m = vec->a[_mi], e1, e2;\
	(({e1 = _m; e2 = _b; comp;}) >= 0) ? (                             \
		(({e1 = _m; e2 = _a; comp;}) >= 0) ? (                         \
			(({e1 = _b; e2 = _a; comp;}) >= 0) ? (                     \
				_b                                                     \
			):(                                                        \
				_a                                                     \
			)                                                          \
		):(                                                            \
			_m                                                         \
		)                                                              \
	):(                                                                \
		(({e1 = _m; e2 = _a; comp;}) >= 0) ? (                         \
			_m                                                         \
		):(                                                            \
			(({e1 = _b; e2 = _a; comp;}) >= 0) ? (                     \
				_a                                                     \
			):(                                                        \
				_b                                                     \
			)                                                          \
		)                                                              \
	);                                                                 \
})//END __HAC_VEC_PIVOT

#define /*size_t*/__HAC_VEC_PARTITION(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp, swap) ({\
	size_t _a = i1, _b = i2 - 1, i, j;                                 \
	base_t _p = __HAC_VEC_PIVOT(base_t, vec, i1, i2, comp), e1, e2;    \
	HAC_VEC_T(base_t) *v = vec;                                        \
	while(_b > _a){                                                    \
		e1 = _p;                                                       \
		e2 = vec->a[_a];                                               \
		if(({comp;}) >= 0){                                            \
			({i = _a; j = _b; swap;});                                 \
			--_b;                                                      \
		}else{                                                         \
			++_a;                                                      \
		}                                                              \
	}                                                                  \
	_a;                                                                \
})//END __HAC_VEC_PARTITION

#define /*void*/__HAC_VEC_QSTEP(base_t, /*HAC_VEC_T**/vec, /*HAC_VEC_T**/tps, comp, swap) ({\
	HAC_PAIR_T(size_t) _ab = HAC_VEC_POPR(HAC_PAIR_T(size_t), tps);    \
	size_t _a = _ab.a, _b = _ab.b, _p;                                 \
	while(_b - _a > 7){                                                \
		_p = __HAC_VEC_PARTITION(base_t, vec, _ab.a, _ab.b, comp, swap);\
		HAC_VEC_PUSHR(HAC_PAIR_T(size_t), tps, HAC_PAIR_MAKE(size_t, _p, _b));\
		_b = _p;                                                       \
	}                                                                  \
	__HAC_VEC_SSORT(base_t, vec, _a, _b, comp, swap);                  \
})//END __HAC_VEC_QSTEP

#define /*void*/__HAC_VEC_QSORT(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp, swap) ({\
	HAC_PAIR_T_NEW(size_t);                                            \
	HAC_VEC_T_NEW(HAC_PAIR_T(size_t));                                 \
	HAC_PAIR_T(size_t) _tpa[1] = {HAC_PAIR_MAKE(size_t, i1, i2)};      \
	HAC_VEC_T(HAC_PAIR_T(size_t)) _tps = HAC_VEC_FROM(HAC_PAIR_T(size_t), 1, _tpa);\
	while(HAC_VEC_LEN(HAC_PAIR_T(size_t), &_tps)){                     \
		__HAC_VEC_QSTEP(base_t, vec, &_tps, comp, swap);               \
	}                                                                  \
	HAC_VEC_DELETE(HAC_PAIR_T(size_t), &_tps);                         \
})//END __HAC_VEC_QSORT

/**
 * @brief Sorts a vector.
 * Uses quicksort, modified to fall back to selection sort if the size of the part being sorted is less than or equal to 7.
 * Because it is written using only macros, there is obviously no recursion.  Instead, the left half is iteratively quicksorted
 * and the right half is popped onto a vector of start/end pairs to be processed when this iteration is finished.  This is looped
 * as long as the vector of pairs is not empty.
 * @param base_t the base type.
 * @param vec a pointer to the vector to sort.
 * @param comp an expression containing e1 and e2 (the elements to be compared).  Should evaluate < 0 if e1 < e2, > 0 if e1 > e2, and == 0 if e1 == e2.  Remember that just using - will sometimes cause overflow.
 * @param swap an expression containing v (a pointer to the vector), i, and j (the indicies to be swapped).
 */
#define HAC_VEC_SORT(base_t, vec, comp, swap) ({                       \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	__HAC_VEC_QSORT(base_t, _vec, 0, _vec->n, comp, swap);             \
})//END HAC_VEC_SORT


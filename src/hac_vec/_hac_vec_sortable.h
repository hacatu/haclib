/**@file _hac_vec_sortable.h*/
#define /*size_t*/__HAC_VEC_AMAX(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp) ({\
	size_t _amax = i1;                                                 \
	base_t _max = (vec)->a[i1], e1, e2;                                \
	for(size_t _i_ = i1 + 1; _i_ < i2; ++_i_){                         \
		e1 = _max;                                                     \
		e2 = (vec)->a[_i_];                                            \
		if(({comp;}) > 0){                                             \
			_max = (vec)->a[_i_];                                      \
			_amax = _i_;                                               \
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

#define /*base_t*/__HAC_VEC_PIVOT_FIRST(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp) (i1)

#define /*base_t*/__HAC_VEC_PIVOT_MEDIAN3(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp) ({\
	size_t _mi = (i1 + i2 - 1)/2;                                      \
	base_t _a_ = (vec)->a[i1], _b_ = (vec)->a[i2 - 1], _m_ = (vec)->a[_mi], e1, e2;\
	(({e1 = _m_; e2 = _b; comp;}) >= 0) ? (                            \
		(({e1 = _m_; e2 = _a_; comp;}) >= 0) ? (                       \
			(({e1 = _b_; e2 = _a_; comp;}) >= 0) ? (                   \
				i2 - 1                                                 \
			):(                                                        \
				i1                                                     \
			)                                                          \
		):(                                                            \
			_mi                                                        \
		)                                                              \
	):(                                                                \
		(({e1 = _m_; e2 = _a_; comp;}) >= 0) ? (                       \
			_mi                                                        \
		):(                                                            \
			(({e1 = _b_; e2 = _a_; comp;}) >= 0) ? (                   \
				i1                                                     \
			):(                                                        \
				i2 - 1                                                 \
			)                                                          \
		)                                                              \
	);                                                                 \
})//END __HAC_VEC_PIVOT_MEDIAN3

#define /*base_t*/__HAC_VEC_PIVOT_RANDOM(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp) (rand_interval(i1, i2 - 1))

#ifndef __HAC_VEC_PIVOT
#define __HAC_VEC_PIVOT __HAC_VEC_PIVOT_MEDIAN3
#endif

#define /*size_t*/__HAC_VEC_PARTITION(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp, swap) ({\
	size_t _a_ = i1, _b_ = i2 - 1, i, j;                               \
	size_t _p_ = __HAC_VEC_PIVOT(base_t, vec, i1, i2, comp), e1, e2;   \
	HAC_VEC_T(base_t) *v = vec;                                        \
	while(1){                                                          \
		while(({e1 = vec->a[_a_]; e2 = vec->a[_p_]; comp;}) < 0){      \
			++_a_;                                                     \
		}                                                              \
		while(({e1 = vec->a[_p_]; e2 = vec->a[_b_]; comp;}) <= 0){     \
			if(_p_ == _b_){                                            \
				_p_ = (_a_ + _b_)/2;                                   \
				({i = _p_; j = _b_; swap;});                           \
				if(_a_ == _b_){                                        \
					break;                                             \
				}                                                      \
				continue;                                              \
			}                                                          \
			--_b_;                                                     \
		}                                                              \
		if(_a_ >= _b_){                                                \
			break;                                                     \
		}                                                              \
		if(_p_ == _b_){                                                \
			_p_ = _a_;                                                 \
		}else if(_a_ == _p_){                                          \
			_p_ = _b_;                                                 \
		}                                                              \
		({i = _a_; j = _b_; swap;});                                   \
	}                                                                  \
	_p_;                                                               \
})//END __HAC_VEC_PARTITION

#define /*void*/__HAC_VEC_QSTEP(base_t, /*HAC_VEC_T**/vec, /*HAC_VEC_T**/tps, comp, swap) ({\
	HAC_PAIR_T(size_t) _ab = HAC_VEC_POPR(HAC_PAIR_T(size_t), tps);    \
	size_t _a = _ab.a, _b = _ab.b, _p;                                 \
	while(_b - _a > 7){                                                \
		_p = __HAC_VEC_PARTITION(base_t, vec, _a, _b, comp, swap);     \
		HAC_VEC_PUSHR(HAC_PAIR_T(size_t), tps, HAC_PAIR_MAKE(size_t, _p + 1, _b));\
		_b = _p;                                                       \
	}                                                                  \
	__HAC_VEC_SSORT(base_t, vec, _a, _b, comp, swap);                  \
})//END __HAC_VEC_QSTEP

#define /*void*/__HAC_VEC_QSORT(base_t, /*HAC_VEC_T**/vec, /*size_t*/i1, /*size_t*/i2, comp, swap) ({\
	HAC_PAIR_T_NEW(size_t);                                            \
	HAC_VEC_T_NEW(HAC_PAIR_T(size_t));                                 \
	HAC_PAIR_T(size_t) _tpa[1] = {HAC_PAIR_MAKE(size_t, i1, i2)};      \
	HAC_VEC_T(HAC_PAIR_T(size_t)) _tps = HAC_VEC_FROM(HAC_PAIR_T(size_t), 1, _tpa);\
	while(_tps.n){                                                     \
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


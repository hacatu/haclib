//_hac_vec_access.h
#define /*base_t*/HAC_VEC_GETX(base_t, vec, i) (*({                    \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	size_t _i = (i);                                                   \
	if(_i < 0){                                                        \
		_i += _vec->n;                                                 \
	}                                                                  \
	&_vec->a[_i];                                                      \
}))//END HAC_VEC_GETX
#define /*void*/HAC_VEC_SWAP(base_t, vec, i, j) ({                     \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	base_t _tmp = _vec->a[i];                                          \
	_vec->a[i] = _vec->a[j];                                           \
	_vec->a[j] = _tmp;                                                 \
	returnvoid;                                                        \
})//END HAC_VEC_SWAP
//swap is an expression contatining v (a pointer to the vector), and i and j (the indicies to be swapped)
//and expr is an expression to generate a random integer between m and n inclusive.
#define /*void*/HAC_VEC_SHUFFLE(base_t, vec, swap, expr) ({            \
	HAC_VEC_T(base_t) *v = (vec);                                      \
	size_t m = 0, n, i, j;                                             \
	for(size_t _i = v->n - 1, _j; _i; --_i){                           \
		n = _i;                                                        \
		_j = ({expr;});                                                \
		i = _i, j = _j;                                                \
		{swap;}                                                        \
	}                                                                  \
})//END HAC_VEC_SHUFFLE


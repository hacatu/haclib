/**@file _hac_vec_collection.h*/
/**
 * @brief Creates a vector with only the elements of a vector meeting a condition.
 * @param base_t the base type.
 * @param vec a pointer the vector to copy.
 * @param expr an expression containing e (the current element).  If true, e will be in the output vector.
 * @return a vector with only the elements of seq meeting expr.
 */
#define HAC_VEC_FILTER(base_t, vec, expr) ({                           \
	HAC_VEC_T(base_t) *_vec = (vec);                                   \
	HAC_VEC_T(base_t) _ret = HAC_VEC_NEW(base_t, _vec->n);             \
	if(_ret.a){                                                        \
		__HAC_VEC_FOREACH(base_t, _vec, ({                             \
			if(({expr;})){                                             \
				HAC_VEC_PUSHR(base_t, &_ret, e);                       \
			}                                                          \
			returnvoid;                                                \
		}));                                                           \
	}                                                                  \
	_ret;/*TODO: add HAC_VEC_TRIM(base_t, vec, size) and use it here.*/\
})//END HAC_VEC_FILTER


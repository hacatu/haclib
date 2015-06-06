//hac_vec_filter_test.v
#include <stdio.h>
#include "hac_vec.h"

/* Tests:
 * Collection:
 *  Filter
 */

typedef struct{int a, b, c;} Triangle;

int isPythag(Triangle t){
	return t.a*t.a + t.b*t.b == t.c*t.c;
}

int main(void){
	HAC_VEC_T_NEW(Triangle);
	HAC_VEC_T(Triangle) triangles = HAC_VEC_EMPTY(Triangle);
	for(int a = 1; a < 5; ++a){
		for(int b = a + 1; b < (12 - a)/2; ++b){
			for(int c = b + 1; c < 11 - a - b; ++c){
				HAC_VEC_PUSHR(Triangle, &triangles, ((Triangle){a, b, c}));
			}
		}
	}/*
	HAC_VEC_T(Triangle) rights =
	//HAC_VEC_FILTER(Triangle, &triangles, isPythag(e));
	({
		__HAC_VEC_Triangle_T *_vec = (&triangles);
		__HAC_VEC_Triangle_T _ret = ({
			size_t _m = (_vec->n);
			({
				Triangle *_a = _m ?
					malloc(_m*sizeof(Triangle))
				:
					NULL;
				(__HAC_VEC_Triangle_T){.a = _a, .n = 0, .m = _a ? _m : 0};
			});
		});
		if(_ret.a){
			({
				Triangle e;
				for(size_t _i = 0; _i < _vec->n; ++_i){
					e = _vec->a[_i];
					{({
						if(({isPythag(e);})){
							({
								__HAC_VEC_Triangle_T *_vec = (&_ret);
								Triangle *_tmp = _vec->a;
								if(_vec->n + 1 > _vec->m){
									_tmp = realloc(_vec->a, _vec->m*2*sizeof(Triangle));
									if(_tmp){
										_vec->a = _tmp;
										_vec->m *= 2;
									}
								}
								if(_tmp){
									_vec->a[_vec->n++] = (e);
								}
								!!_tmp;
							});
						}
						returnvoid;
					});}
				}
				returnvoid;
			});
		}
		_ret;
	});*/
	HAC_VEC_DELETE(Triangle, &triangles);/*
	Triangle right = HAC_VEC_GET(Triangle, &rights, 0);
	printf("%i, %i, %i: %i", right.a, right.b, right.c, right.a*right.b*right.c);
	HAC_VEC_DELETE(Triangle, &rights);*/
}


# HACLIB

Haclib adds higher-order, generic types to C.  These include vectors (self-resizing arrays), sequences (linked lists),
and trees.  These data structures are implemented as macros in headers with the base type being the first parameter,
so specific code is generated for each type and there is no overhead from tags or void pointers.  Note that because of a
peculiarity in C where identical struct types are not compatible (eg `struct{int i;} a; struct{int i;} b = a;` will not
work), the macros `*_T_NEW(base_t)` must be used once before the macros `*_T(base_t)` to setup a typedef.  Example with vectors:

	#include <stdio.h>
	#include "hac_vec.h"
	
	int main(void){
		HAC_VEC_T_NEW(int);
		HAC_VEC_T(int) vec = HAC_VEC_FROM(int, 1, &(int[1]){2});
		for(int i = 2; i < 100; ++i){
			if(HAC_VEC_ALL(int, &vec, i%e)){
				HAC_VEC_PUSHR(int, &vec, i);
			}
		}
		printf("%i primes:\n", (int)HAC_VEC_LEN(int, &vec));
		HAC_VEC_FOREACH(int, &vec, printf("%i\n", e));
		HAC_VEC_DELETE(int, &vec);
	}

The code makes heavy use of statement expressions (the `({})` things), which are not standard C but supported by at least GCC and
Clang.

The code for the data types is divided into separate files for different "typeclasses", which are only nominal but denote certain
behaviors.  For example, the `functor` interface requires `map` and `foreach`, so these macros are placed in _hac_vec_functor.h.

To use the types, have a look at the typedefs in the `*_T_NEW(base_t)` macros located in the main headers
(ie the ones not beginning with an underscore).  Usually you can use either `vec.n` or `HAC_VEC_LEN(base_t, &vec)` to get the
length of a vector, `vec.a[i]` or `HAC_VEC_GET(base_t, &vec, i)` to get the ith element, and so on.

Take a look at the test files to see some actual examples.


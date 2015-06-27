/**@file _hac_avl_check.h*/
#ifndef __HAC_AVL_A
#define __HAC_AVL_A(n, s) (*(void**)(n + s - 3*sizeof(void*)))
#define __HAC_AVL_B(n, s) (*(void**)(n + s - 2*sizeof(void*)))
#define __HAC_AVL_P(n, s) (*(void**)(n + s - 1*sizeof(void*)))
#define __HAC_AVL_K(n, s) (*(int*)(n + s - 3*sizeof(void*) - 1*sizeof(int)))
#endif
static int __HAC_AVL_CHECK_R(void *root, size_t size){
	if(!root){
		return -1;
	}
	return !__HAC_AVL_P(root, size);
}
static int __HAC_AVL_CHECK_P(void *root, size_t size){
	if(!root){
		return -1;
	}
	if((__HAC_AVL_A(root, size) && root != __HAC_AVL_P(__HAC_AVL_A(root, size), size)) ||
	   (__HAC_AVL_B(root, size) && root != __HAC_AVL_P(__HAC_AVL_B(root, size), size))){
		printf("CHECK_P failed at %p\n", root);
		return 0;
	}
	return __HAC_AVL_CHECK_P(__HAC_AVL_A(root, size), size) &&
	       __HAC_AVL_CHECK_P(__HAC_AVL_B(root, size), size);
}
static volatile int __HAC_AVL_CHECK_K(void *root, size_t size, size_t *height){
	if(!root){
		*height = 0;
		return -1;
	}
	size_t heighta, heightb;
	if(!(__HAC_AVL_CHECK_K(__HAC_AVL_A(root, size), size, &heighta) &&
	     __HAC_AVL_CHECK_K(__HAC_AVL_B(root, size), size, &heightb))){
		*height = ((heighta < heightb) ? heightb : heighta) + 1;
		return 0;
	}
	*height = ((heighta < heightb) ? heightb : heighta) + 1;
	return heighta - heightb == __HAC_AVL_K(root, size);
}
static int __HAC_AVL_CHECK_AVL(void *root, size_t size){
	if(!root){
		return -1;
	}
	return (-2 < __HAC_AVL_K(root, size) && __HAC_AVL_K(root, size) < 2) &&
		   __HAC_AVL_CHECK_AVL(__HAC_AVL_A(root, size), size) &&
		   __HAC_AVL_CHECK_AVL(__HAC_AVL_B(root, size), size);
}
#ifndef __HAC_AVL_CHECK
#define __HAC_AVL_CHECK(base_t, avl) __HAC_AVL_NODE_CHECK(base_t, (avl)->r)
#define __HAC_AVL_NODE_CHECK(base_t, root) ({                          \
	void *_root = (root);                                              \
	int _ret = 1;                                                      \
	size_t _height;                                                    \
	if(!_root){                                                        \
		puts("null root");                                             \
	}                                                                  \
	if(!__HAC_AVL_CHECK_R(_root, sizeof(__HAC_AVL_NODE_T(base_t)))){   \
		puts("CHECK_R failed");                                        \
		_ret = 0;                                                      \
	}                                                                  \
	if(!__HAC_AVL_CHECK_P(_root, sizeof(__HAC_AVL_NODE_T(base_t)))){   \
		puts("CHECK_P failed");                                        \
		_ret = 0;                                                      \
	}                                                                  \
	if(!__HAC_AVL_CHECK_K(_root, sizeof(__HAC_AVL_NODE_T(base_t)), &_height)){\
		puts("CHECK_K failed");                                        \
		_ret = 0;                                                      \
	}                                                                  \
	_ret;                                                              \
})//END __HAC_AVL_NODE_CHECK
#endif


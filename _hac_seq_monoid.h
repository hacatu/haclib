/**@file _hac_seq_monoid.h*/
/**
 * @brief Checks if a sequence is empty.
 * @param base_t the base type.
 * @param seq a pointer to the sequence.
 * @return 1 if the sequence is empty, 0 otherwise.
 */
#define HAC_SEQ_IS_EMPTY(base_t, seq) (!(seq)->n)

#define /*void*/__HAC_SEQ_MERGE(base_t, /*HAC_SEQ_T**/seqa, /*HAC_SEQ_T**/seqb) ({\
	if((seqa)->n && (seqb)->n){                                        \
		(seqa)->b->b = (seqb)->a;                                      \
		(seqb)->a->a = (seqa)->b;                                      \
		(seqb)->a = (seqa)->a;                                         \
		(seqa)->b = (seqb)->b;                                         \
		(seqa)->n += (seqb)->n;                                        \
		(seqb)->n = (seqa)->n;                                         \
	}                                                                  \
})//END __HAC_SEQ_MERGE

/**
 * @brief Merges two sequences into one.
 * The last element of seqa and the first element of seqb are linked together,
 * then the last element of seqa is set to be the last element of seqb and the first element of seqb is set to be the first element of seqa,
 * then the length of each is set to the sum of their lengths.  This makes both sequences references to the same linked list,
 * so you should probably void one by setting it to HAC_SEQ_EMPTY(base_t).  This macro does not return any value.
 * Note that if either sequence is empty, nothing will be done.
 * @param base_t the base type.
 * @param seqa a pointer to the first sequence.
 * @param seqb a pointer to the second sequence.
 */
#define HAC_SEQ_MERGE(base_t, seqa, seqb) ({                           \
	HAC_SEQ_T(base_t) *_seqa = (seqa), *_seqb = (seqb);                \
	__HAC_SEQ_MERGE(base_t, _seqa, _seqb);                             \
})//END HAC_SEQ_MERGE

/**
 * @brief Combines two sequences to make a new sequence.
 * Creates a copy of each sequence using HAC_SEQ_COPY(base_t, seq), then merges the copies using HAC_SEQ_MERGE(baset, seqa, seqb).
 * Does not deep copy the values whatsoever.  Note that if either list is empty, the lists will not be merged.
 * In this case, a copy of the first list will be returned.
 * @param base_t the base type.
 * @param seqa a pointer to the first sequence.
 * @param seqb a pointer to the second sequence.
 * @return a combination of the two sequences.
 */
#define HAC_SEQ_COMBINE(base_t, seqa, seqb) ({                         \
	HAC_SEQ_T(base_t) _seqa = HAC_SEQ_COPY(base_t, (seqa)), _seqb = HAC_SEQ_COPY(base_t, (seqb));\
	__HAC_SEQ_MERGE(base_t, &_seqa, &_seqb);                           \
	_seqa;                                                             \
})//END HAC_SEQ_COMBINE

/**
 * @brief Tests if a condition applies to all elements of a sequence.
 * Reads values from left to right and stops early if one does not meet the condition.
 * @param base_t the base type.
 * @param seq a pointer to the sequence.
 * @param expr an expression containing e (the current element), evaluating to 1 if true and 0 if false.
 * @return 1 if the condition is 1 for all elements of the sequence, 0 otherwise.
 */
#define HAC_SEQ_ALL(base_t, seq, expr) ({                              \
	const HAC_SEQ_T(base_t) *_seq = (seq);                             \
	int _r = 1;                                                        \
	base_t e;                                                          \
	for(__HAC_SEQ_NODE_T(base_t) *_node = _seq->a; _r && _node; _node = _node->b){\
		e = _node->v;                                                  \
		_r = _r && ({expr;});                                          \
	}                                                                  \
	_r;                                                                \
})//END HAC_SEQ_ALL

/**
 * @brief Tests if a condition applies to any element in a sequence.
 * Reads values from left to right and stops early if one meets the condition.
 * @param base_t the base type.
 * @param seq a pointer to the sequence.
 * @param expr an expression containing e (the current element), evaluating to 1 if true and 0 if false.
 * @return 1 if the condition is 1 for any element in the sequence, 0 otherwise.
 */
#define HAC_SEQ_ANY(base_t, seq, expr) ({                              \
	const HAC_SEQ_T(base_t) *_seq = (seq);                             \
	int _r = 0;                                                        \
	base_t e;                                                          \
	for(__HAC_SEQ_NODE_T(base_t) *_node = _seq->a; (!_r) && _node; _node = _node->b){\
		e = _node->v;                                                  \
		_r = _r || ({expr;});                                          \
	}                                                                  \
	_r;                                                                \
})//END HAC_SEQ_ANY

/**
 * @brief Tests if a sequence contains a value.
 * Reads values from left to right and stops early if one matches.
 * Note that this is O(n) time and if you want to do a lot of checks like this you should look into using a different data structure.
 * @param base_t the base type.
 * @param seq a pointer to the sequence.
 * @param elem the value to check for in the sequence.
 * @param comp an expression containing e1 and e2 (the two elements to be compared) and returning 0 if they are equal.
 * @return 1 if elem is in seq, 0 otherwise.
 */
#define HAC_SEQ_CONTAINS(base_t, seq, elem, comp) HAC_VEC_ANY(base_t, vec, ({base_t e1 = elem; base_t e2 = e; !({comp});}))


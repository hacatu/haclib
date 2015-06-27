/**
 * @file hac_util.h
 * @brief Misc.
 */
#ifndef __HAC_UTIL__
#define __HAC_UTIL__

#include <stdlib.h>

/**
 * Explicitly create a void value, suitable to be the last statement in a statment expression that should be void.
 */
#define returnvoid ((void)0)

#if defined(__GNUC__) && !defined(__clang__)
/**
 * Example: AUTOTYPEOF(expr) identifier = expr;
 * If you want to get the type of something for any purpose other than declaring one variable, you should use __typeof__(expr).
 */
#define AUTOTYPEOF(expr) __auto_type
#else
#define AUTOTYPEOF(expr) __typeof__(expr)
#endif

/**
 * @brief evaluate an expression with a value bound to a variable.
 * Sets name to val.  If val fails cond, do nothing.  Otherwise, do expr.
 * Example: HAC_WITH(FILE *f, fopen("file.txt", "w"), f, ({fprintf(f, "Hello with"); fclose(f);}));
 * @param name the identifier to set to val, with type if not already declared.
 * @param val the value to bind to name.
 * @param cond a check for val being valid.
 * @param expr the expression to evaluate.
 */
#define HAC_WITH(name, val, cond, expr) ({/*TODO: use HAC_WITH more*/  \
	name = val;                                                        \
	if(({cond;})){                                                     \
		expr;                                                          \
	}                                                                  \
})//END HAC_WITH

<<<<<<< HEAD
/**
 * @brief absolute value.
 * Takes the absolute value of a basic real numeric type (complex will not work).
 * @param a the quantity to take the absolute value of
 * @return the absolute value of a.
 */
#define HAC_ABS(a) ({                                                  \
	AUTOTYPEOF(a) _a = (a);                                            \
	_a < 0 ? -_a : _a;                                                 \
})//END HAC_ABS

/**
 * @brief sign.
 * Takes the sign value of a basic real numeric type (complex will not work).
 * This is -1 for negatives, +1 for positives, and 0 for 0.
 * @param a the quantity to take the sign value of
 * @return the sign value of a.
 */
#define HAC_SGN(a) ({                                                  \
	AUTOTYPEOF(a) _a = (a);                                            \
	_a < 0 ? -1 : _a > 0 ? 1 : 0;                                      \
})//END HAC_SGN

/**
 * @brief maximum of two values.
 * @param a the first value.
 * @param b the second value.
 * @return the larger of a and b.
 */
#define HAC_MAX(a, b) ({                                               \
	AUTOTYPEOF(a) _a = (a);                                            \
	AUTOTYPEOF(b) _b = (b);                                            \
	_b > _a ? _b : _a;                                                 \
})//END HAC_MAX

/**
 * @brief minimum of two values.
 * @param a the first value.
 * @param b the second value.
 * @return the smaller of a and b.
 */
#define HAC_MIN(a, b) ({                                               \
	AUTOTYPEOF(a) _a = (a);                                            \
	AUTOTYPEOF(b) _b = (b);                                            \
	_b < _a ? _b : _a;                                                 \
})//END HAC_MIN

=======
>>>>>>> e449e65b666b5be957b45a65357d77ff12dcdb10
#endif


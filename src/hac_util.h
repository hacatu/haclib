/**
 * @file hac_util.h
 * @brief Misc.
 */
#ifndef __HAC_UTIL__
#define __HAC_UTIL__

#include <stdlib.h>
#include <stddef.h>

/**
 * Explicitly create a void value, suitable to be the last statement in a statment expression that should be void.
 */
#define returnvoid ((void)0)

#define __HAC_PASTE(a, b) (a##b)

/**
 * Token pasting wrapped in a macro to ensure argument evaluation
 */
#define HAC_PASTE(a, b) __HAC_PASTE(a, b)

#if defined(__GNUC__) && !defined(__clang__)
/**
 * Example: HAC_AUTO_T(expr) identifier = expr;
 * If you want to get the type of something for any purpose other than declaring one variable, you should use __typeof__(expr).
 */
#define HAC_AUTO_T(expr) __auto_type
#else
#define HAC_AUTO_T(expr) __typeof__(expr)
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

/**
 * @brief absolute value.
 * Takes the absolute value of a basic real numeric type (complex will not work).
 * @param a the quantity to take the absolute value of
 * @return the absolute value of a.
 */
#define HAC_ABS(a) ({                                                  \
	HAC_AUTO_T(a) _a = (a);                                            \
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
	HAC_AUTO_T(a) _a = (a);                                            \
	_a < 0 ? -1 : _a > 0 ? 1 : 0;                                      \
})//END HAC_SGN

/**
 * @brief maximum of two values.
 * @param a the first value.
 * @param b the second value.
 * @return the larger of a and b.
 */
#define HAC_MAX(a, b) ({                                               \
	HAC_AUTO_T(a) _a = (a);                                            \
	HAC_AUTO_T(b) _b = (b);                                            \
	_b > _a ? _b : _a;                                                 \
})//END HAC_MAX

/**
 * @brief minimum of two values.
 * @param a the first value.
 * @param b the second value.
 * @return the smaller of a and b.
 */
#define HAC_MIN(a, b) ({                                               \
	HAC_AUTO_T(a) _a = (a);                                            \
	HAC_AUTO_T(b) _b = (b);                                            \
	_b < _a ? _b : _a;                                                 \
})//END HAC_MIN

/**
 * @brief a do nothing function to set breakpoints in these macros.
 * If in gdb, do `breakpoint HAC_BREAKPOINT` or `breakpoint HAC_BREAKPOINT if c`
 * and then `command <number>` with the number of the breakpoint.
 * Set the command to `frame 1`: this will back out of HAC_BREAKPOINT and let you debug some real code.
 * @param msg any description you like, gdb will display it for you, to aid in figuring out which HAC_BREAKPOINT is stopped at.
 * @param c a condition for the breakpoint.  These arguments are not actually used by HAC_BREAKPOINT because it does nothing,
 * but are useful for gdb.
 */
void HAC_BREAKPOINT(const char *msg, int c){}

#endif


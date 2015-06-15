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

#endif


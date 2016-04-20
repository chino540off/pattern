#ifndef COUNTER_H_
# define COUNTER_H_

# include <stdio.h>

struct counter_s
{
	unsigned int offset;
	unsigned int size;

	unsigned int value;
	char const * pattern;
};

typedef struct counter_s counter_t;

/** 
 * @brief Create a new counter
 * 
 * @param value the initialization value
 * @param pattern the pattern to be counted
 * 
 * @return 
 */
counter_t * counter_new(unsigned int value, char const * pattern);

/** 
 * @brief Print a counter
 * 
 * @param c a counter
 * @param s the output stream
 */
void counter_print(counter_t const * c, FILE * s);

/** 
 * @brief Compare 2 counters
 * 
 * @param a lhs
 * @param b rhs
 * 
 * @return the difference between them
 */
int counter_cmp(counter_t const * a, counter_t const * b);
/** 
 * @brief Duplicate a counter
 * 
 * @param c a counter
 * 
 * @return a new counter with c's values
 */
counter_t * counter_dup(counter_t const * c);

/** 
 * @brief Free a counter
 * 
 * @param c a counter
 */
void counter_free(counter_t * c);

#endif /** !COUNTER_H_  */


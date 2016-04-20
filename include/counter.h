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
 * @brief 
 * 
 * @param value
 * @param pattern
 * 
 * @return 
 */
counter_t * counter_new(unsigned int value, char const * pattern);

/** 
 * @brief 
 * 
 * @param c
 * @param s
 */
void counter_print(counter_t const * c, FILE * s);

/** 
 * @brief 
 * 
 * @param a
 * @param b
 * 
 * @return 
 */
int counter_cmp(counter_t const * a, counter_t const * b);
/** 
 * @brief 
 * 
 * @param c
 * 
 * @return 
 */
counter_t * counter_dup(counter_t const * c);

/** 
 * @brief 
 * 
 * @param c
 */
void counter_free(counter_t * c);

#endif /** !COUNTER_H_  */


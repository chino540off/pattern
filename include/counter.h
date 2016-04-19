#ifndef COUNTER_H_
# define COUNTER_H_

# include <stdlib.h>
# include <stdio.h>

struct counter_s
{
	unsigned int value;
	char const * pattern;
};

typedef struct counter_s counter_t;

counter_t * counter_new(unsigned int value, char const * pattern)
{
	counter_t * c = 0;

	if ((c = malloc(sizeof (counter_t))) == 0)
		return 0;

	c->value = value;
	c->pattern = pattern;

	return c;
}

void counter_print(counter_t const * c, FILE * s)
{
	fprintf(s, "pattern %s == %d", c->pattern, c->value);
}

counter_t * counter_dup(counter_t const * c)
{
	return counter_new(c->value, c->pattern);
}

void counter_free(counter_t * c)
{
	free(c);
}

#endif /** !COUNTER_H_  */


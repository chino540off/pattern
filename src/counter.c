#include <stdlib.h>
#include <string.h>

#include <counter.h>

counter_t * counter_new(unsigned int value, char const * pattern)
{
	counter_t * c = 0;

	if ((c = malloc(sizeof (counter_t))) == 0)
		return 0;

	c->size = strlen(pattern);
	c->value = value;
	c->pattern = pattern;

	if ((c->used = malloc(c->size + 1)) == 0)
	{
		free(c);
		return 0;
	}
	memset(c->used, 0x0, c->size + 1);

	return c;
}

void counter_print(counter_t const * c, FILE * s)
{
	fprintf(s, "pattern %s == %d", c->pattern, c->value);
}

int counter_cmp(counter_t const * a, counter_t const * b)
{
	return strcmp(a->pattern, b->pattern);
}

counter_t * counter_dup(counter_t const * c)
{
	counter_t * ret = counter_new(c->value, c->pattern);

	if (ret != 0)
		memcpy(ret->used, c->used, c->size + 1);
	return ret;
}

void counter_free(counter_t * c)
{
	free(c->used);
	free(c);
}


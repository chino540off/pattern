#include <stdlib.h>
#include <string.h>

#include <mapper.h>
#include <counter.h>

int c_cmp(void const * a, void const * b)
{
	return strcmp(((counter_t const *)a)->pattern, ((counter_t const *)b)->pattern);
}

mapper_t * mapper_new(unsigned int n, char const * patterns[])
{
	mapper_t * mapper = 0;

	if ((mapper = malloc(sizeof (mapper_t))) == 0)
		return 0;

	mapper->n = n;

	if ((mapper->runners = malloc(mapper->n * sizeof (runner_t))) == 0)
	{
		free(mapper);
		return 0;
	}

	for (unsigned int i = 0; patterns[i]; ++i)
		mapper->runners[0].list = list_node_insert(mapper->runners[0].list, counter_new(0, patterns[i]), c_cmp);

	for (unsigned int i = 1; i < n; ++i)
		mapper->runners[i].list = list_node_dup(mapper->runners[0].list, (list_t_dup_f)counter_dup);

	return mapper;
}

void mapper_free(mapper_t * mapper)
{
	for (unsigned int i = 0; i < mapper->n; ++i)
		list_node_free(mapper->runners[i].list, (list_t_free_f)counter_free);

	free(mapper->runners);
	free(mapper);
}


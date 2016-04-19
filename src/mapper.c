#include <stdlib.h>
#include <string.h>

#include <mapper.h>
#include <counter.h>

int c_cmp(void const * a, void const * b)
{
	return strcmp(((counter_t const *)a)->pattern, ((counter_t const *)b)->pattern);
}

mapper_t * mapper_new(unsigned int n, char const * argv[])
{
	mapper_t * mapper = 0;

	if ((mapper = malloc(sizeof (mapper_t))) == 0)
		return 0;

	mapper->n = n;

	if ((mapper->arr = malloc(mapper->n * sizeof (list_node_t*))) == 0)
	{
		free(mapper);
		return 0;
	}

	for (unsigned int i = 0; argv[i]; ++i)
		mapper->arr[0] = list_node_insert(mapper->arr[0], counter_new(0, argv[i]), c_cmp);

	for (unsigned int i = 1; i < n; ++i)
		mapper->arr[i] = list_node_dup(mapper->arr[0], (list_t_dup_f)counter_dup);

	return mapper;
}

void mapper_free(mapper_t * mapper)
{
	for (unsigned int i = 0; i < mapper->n; ++i)
		list_node_free(mapper->arr[i], (list_t_free_f)counter_free);

	free(mapper->arr);
	free(mapper);
}


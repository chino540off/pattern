#include <stdlib.h>
#include <string.h>

#include <counter.h>
#include <mapper.h>
#include <pattern.h>

int main(int argc, char const * argv[])
{
	if (argc < 4)
		return 1;

	char const *	filename = argv[1];
	unsigned int	n = atoi(argv[2]);

	if ((int)n <= 0)
	{
		return 1;
	}

	mapper_t *		mapper;
	pattern_ctx_t	contexts[n];
	void *			pcontexts[n];

	for (unsigned int i = 0; i < n; ++i)
	{
		contexts[i].list = 0;
		contexts[i].filename = filename;

		for (unsigned int j = 3; argv[j]; ++j)
			contexts[i].list = list_node_insert(contexts[i].list, counter_new(0, argv[j]), (list_t_cmp_f)counter_cmp);

		pcontexts[i] = &contexts[i];
	}

	mapper = mapper_new(n, pcontexts);
	mapper_run(mapper, pattern_map);
	mapper_free(mapper);

	for (unsigned int i = 0; i < n; ++i)
		list_node_free(contexts[i].list, (list_t_free_f)counter_free);

	return 0;
}

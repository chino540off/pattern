#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <counter.h>
#include <pattern.h>

static void print(void const * elt, void * data)
{
	(void)(data);
	counter_t * counter = (counter_t *)elt;

	counter_print(counter, stdout);
	fprintf(stdout, "\n");
}

int main(int argc, char const * argv[])
{
	if (argc < 4)
	{
		fprintf(stderr, "Usage: %s FILE NBTHREAD [PATTERNS]...\n", argv[0]);
		return 1;
	}

	char const *	filename = argv[1];
	if (access(filename, R_OK) != 0)
	{
		perror(filename);
		return 1;
	}

	unsigned int	n = atoi(argv[2]);
	if ((int)n <= 0 || n >= 64)
	{
		fprintf(stderr, "NBTHREAD must be a positive and superior than zero or less than 64\n");
		return 1;
	}

	cluster_t *		cluster;
	pattern_ctx_t	contexts[n];
	void *			pcontexts[n];

	for (unsigned int i = 0; i < n; ++i)
	{
		contexts[i].list = slist_new((slist_node_t_free_f)counter_free, (slist_node_t_dup_f)counter_dup, (slist_node_t_cmp_f)counter_cmp);
		contexts[i].filename = filename;

		for (unsigned int j = 3; argv[j]; ++j)
		{
			counter_t * c = counter_new(0, argv[j]);
			contexts[i].list = slist_insert(contexts[i].list, c);
		}

		pcontexts[i] = &contexts[i];
	}

	cluster = cluster_new(n, pcontexts);

	cluster_map(cluster, pattern_map);

	pattern_ctx_t * result = cluster_reduce(cluster, pattern_reduce);

	slist_foreach(result->list, print, 0);

	cluster_free(cluster);
	slist_free(result->list);

	return 0;
}

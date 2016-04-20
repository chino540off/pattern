#include <stdlib.h>
#include <string.h>

#include <counter.h>
#include <pattern.h>

static void reduce(void const * elt, void * data)
{
	slist_node_t ** p = (slist_node_t **)data;
	counter_t * c_cur = (counter_t *)elt;
	counter_t * c_res = (counter_t *)(*p)->elt;

	c_res->value += c_cur->value;

	*p = (*p)->next;
}

static void print(void const * elt, void * data)
{
	counter_t * counter = (counter_t *)elt;
	counter_print(counter, stdout);
	fprintf(stdout, "\n");
}

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

	cluster_t *		cluster;
	pattern_ctx_t	contexts[n];
	void *			pcontexts[n];

	for (unsigned int i = 0; i < n; ++i)
	{
		contexts[i].list = 0;
		contexts[i].filename = filename;

		for (unsigned int j = 3; argv[j]; ++j)
		{
			counter_t * c = counter_new(0, argv[j]);
			contexts[i].list = slist_node_insert(contexts[i].list, c, (slist_node_t_cmp_f)counter_cmp);
		}

		pcontexts[i] = &contexts[i];
	}

	cluster = cluster_new(n, pcontexts);
	cluster_run(cluster, pattern_map);
	cluster_free(cluster);

	slist_node_t * result = 0;

	for (unsigned int j = 3; argv[j]; ++j)
	{
		counter_t * c = counter_new(0, argv[j]);
		result = slist_node_insert(result, c, (slist_node_t_cmp_f)counter_cmp);
	}

	for (unsigned int i = 0; i < n; ++i)
	{
		slist_node_t * p = result;
		slist_node_foreach(contexts[i].list, reduce, &p);

		slist_node_free(contexts[i].list, (slist_node_t_free_f)counter_free);
	}

	slist_node_foreach(result, print, 0);

	slist_node_free(result, (slist_node_t_free_f)counter_free);

	return 0;
}

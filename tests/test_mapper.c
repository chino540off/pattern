#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <counter.h>
#include <mapper.h>

#define NMAPPER 4

int c_cmp(void const * a, void const * b)
{
	return strcmp(((counter_t const *)a)->pattern, ((counter_t const *)b)->pattern);
}

struct counter_ctx_s
{
	list_node_t * list;
};
typedef struct counter_ctx_s counter_ctx_t;


void c_init(void const * a, void * data)
{
	counter_t * c = (counter_t *)a;
	unsigned int * rv = (unsigned int *)data;
	c->value = *rv;
}

void * r_init(void * data)
{
	runner_t * r = (runner_t *)data;
	counter_ctx_t * ctx = (counter_ctx_t *)r->data;

	list_node_foreach(ctx->list, c_init, &r->index);

	pthread_exit(data);
}

int main(int argc,
		 char const ** argv)
{
	if (argc < 3)
		return 1;

	unsigned int	n = NMAPPER;
	mapper_t *		mapper;
	counter_ctx_t	contexts[n];
	void *			pcontexts[n];

	for (unsigned int i = 0; i < NMAPPER; ++i)
	{
		contexts[i].list = 0;

		for (unsigned int j = 1; argv[j]; ++j)
			contexts[i].list = list_node_insert(contexts[i].list, counter_new(0, argv[j]), c_cmp);

		pcontexts[i] = &contexts[i];
	}

	mapper = mapper_new(n, pcontexts);
	mapper_run(mapper, r_init);

	for (unsigned int i = 0; i < NMAPPER; ++i)
	{
		list_node_t * p = contexts[i].list;

		while (p)
		{
			counter_t * c = (counter_t *)p->elt;

			assert(c->value == i);
			p = p->next;
		}

		list_node_free(contexts[i].list, (list_t_free_f)counter_free);
	}

	mapper_free(mapper);
}

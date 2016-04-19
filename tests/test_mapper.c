#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <counter.h>
#include <mapper.h>

void c_init(void const * a, void * data)
{
	counter_t * c = (counter_t *)a;
	unsigned int * rv = (unsigned int *)data;
	c->value = *rv;
}

void * r_init(void * data)
{
	runner_t * r = (runner_t *)data;

	list_node_foreach(r->list, c_init, &r->index);

	pthread_exit(data);
}

int main(int argc,
		 char const ** argv)
{
	if (argc < 3)
		return 1;

	unsigned int	n = atoi(argv[1]);
	mapper_t *		mapper;

	mapper = mapper_new(n, argv + 2);
	mapper_run(mapper, r_init);

	for (unsigned int i = 0; i < mapper->n; ++i)
	{
		list_node_t * p = mapper->runners[i].list;

		while (p)
		{
			counter_t * c = (counter_t *)p->elt;

			assert(c->value == i);
			p = p->next;
		}
	}

	mapper_free(mapper);
}

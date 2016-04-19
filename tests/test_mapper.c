#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <counter.h>
#include <mapper.h>

void c_print(void const * a, void * data)
{
	FILE * s = (FILE *)data;

	counter_print((counter_t const *)a, s);
	fprintf(s, " ");
}

void * doit(void * data)
{
	runner_t * r = (runner_t *)data;

	fprintf(stdout, "[%d]", r->index);
	list_node_foreach(r->list, c_print, stdout);
	fprintf(stdout, "\n");

	pthread_exit(data);
}

int main(int argc,
		 char const ** argv)
{
	if (argc < 3)
		return 1;

	unsigned int	len = atoi(argv[1]);
	mapper_t *		mapper;

	mapper = mapper_new(len, argv + 2);
	mapper_run(mapper, doit);
	mapper_free(mapper);
}

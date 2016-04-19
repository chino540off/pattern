#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <counter.h>
#include <mapper.h>

void c_print(void const * a, void * data)
{
	FILE * s = (FILE *)data;
	counter_print((counter_t const *)a, s);
	fprintf(s, "\n");
}

int main(int argc,
		 char const ** argv)
{
	if (argc < 3)
		return 1;

	unsigned int	len = atoi(argv[1]);
	mapper_t *		mapper;

	mapper = mapper_new(len, argv + 2);

	for (unsigned int i = 0; i < mapper->n; ++i)
	{
		list_node_foreach(mapper->arr[i], c_print, stdout);
		fprintf(stdout, "\n");
	}

	mapper_free(mapper);
}

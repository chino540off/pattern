#include <stdlib.h>
#include <string.h>

#include <counter.h>
#include <mapper.h>

static int c_cmp(void const * a, void const * b)
{
	return strcmp(((counter_t const *)a)->pattern, ((counter_t const *)b)->pattern);
}

struct counter_ctx_s
{
	list_node_t * list;
	char const * filename;
};
typedef struct counter_ctx_s counter_ctx_t;

static void * do_count(void * data)
{
	runner_t * r = (runner_t *)data;
	counter_ctx_t * ctx = (counter_ctx_t *)r->data;

	FILE * fd = 0;

	if ((fd = fopen(ctx->filename, "r")) == 0)
	{
		perror("fopen: ");
		pthread_exit(0);
	}

	fseek(fd, 0, SEEK_END);
	unsigned int f_size = ftell(fd);

	unsigned int slice = f_size / r->n;
	unsigned int r_size = (r->index == r->n - 1) ? slice + (f_size % r->n) : slice;

	printf("f_size of file: %d, part to be read: %d\n", f_size, r_size);
	printf("index to start: %d\n", slice * r->index);
	fseek(fd, slice * r->index, SEEK_SET);

	if (fclose(fd))
	{
		perror("fclose: ");
		pthread_exit(0);
	}

	pthread_exit(data);
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

	mapper_t *		mapper;
	counter_ctx_t	contexts[n];
	void *			pcontexts[n];

	for (unsigned int i = 0; i < n; ++i)
	{
		contexts[i].list = 0;
		contexts[i].filename = filename;

		for (unsigned int j = 3; argv[j]; ++j)
			contexts[i].list = list_node_insert(contexts[i].list, counter_new(0, argv[j]), c_cmp);

		pcontexts[i] = &contexts[i];
	}

	mapper = mapper_new(n, pcontexts);
	mapper_run(mapper, do_count);
	mapper_free(mapper);

	return 0;
}

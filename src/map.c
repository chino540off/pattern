#include <stdio.h>

#include <map.h>
#include <mapper.h>
#include <pattern.h>

void * do_map(void * data)
{
	runner_t * r = (runner_t *)data;
	pattern_ctx_t * ctx = (pattern_ctx_t *)r->data;

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


#include <part_stream.h>
#include <map.h>
#include <mapper.h>
#include <pattern.h>
#include <counter.h>

void * do_map(void * data)
{
	runner_t * r = (runner_t *)data;
	pattern_ctx_t * ctx = (pattern_ctx_t *)r->data;
	part_stream_t * ps;

	if ((ps = part_stream_open(ctx->filename, "r", r->index, r->n)) == 0)
	{
		perror("part_stream_open");
		pthread_exit(0);
	}

	part_stream_seek(ps, 0);

	while (!part_stream_eop(ps))
	{
		char c = part_stream_getc(ps);

	}

	if (part_stream_close(ps))
	{
		perror("part_stream_close");
		pthread_exit(0);
	}

	pthread_exit(data);
}


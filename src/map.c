#include <part_stream.h>
#include <pattern.h>
#include <counter.h>

struct map_state_s
{
	char c;
	int current;
};
typedef struct map_state_s map_state_t;

static void check_current_char(void const * elt, void * data)
{
	counter_t * counter = (counter_t *)elt;
	map_state_t * state = (map_state_t *)data;

	/// Current read char
	if (counter->pattern[counter->offset] == state->c)
	{
		if (counter->offset == 0)
			++state->current;

		++counter->offset;

		if (counter->offset >= counter->size)
		{
			++counter->value;
			counter->offset = 0;
			--state->current;
		}
	}
	else
	{
		if (counter->offset != 0)
		{
			counter->offset = 0;
			--state->current;
		}

	}
}

runner_t * pattern_map(runner_t * r)
{
	pattern_ctx_t * ctx = (pattern_ctx_t *)r->data;
	part_stream_t * ps;
	map_state_t state;

	state.current = 0;

	if ((ps = part_stream_open(ctx->filename, "r", r->index, r->n)) == 0)
	{
		perror("part_stream_open");
		pthread_exit(0);
	}

	part_stream_seek(ps, 0);

	while (!part_stream_eop(ps) || state.current > 0)
	{
		state.c = part_stream_getc(ps);

		//if (r->index == 0)
		//	printf("%c", state.c);

		slist_node_foreach(ctx->list, check_current_char, &state);
	}

	//if (r->index == 0)
	//	printf("current == %d\n", state.current);

	if (part_stream_close(ps))
	{
		perror("part_stream_close");
		pthread_exit(0);
	}

	pthread_exit(r);
}


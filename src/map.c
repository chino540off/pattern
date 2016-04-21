#include <pstream.h>
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

mapper_t * pattern_map(mapper_t * r)
{
	pattern_ctx_t * ctx = (pattern_ctx_t *)r->data;
	pstream_t * ps;
	map_state_t state;

	state.current = 0;

	if ((ps = pstream_open(ctx->filename, "r", r->index, r->n)) == 0)
	{
		perror("pstream_open");
		pthread_exit(0);
	}

	pstream_seek(ps, 0);

	while (!pstream_eop(ps) || state.current > 0)
	{
		state.c = pstream_getc(ps);

		//if (r->index == 0)
		//	printf("%c", state.c);

		slist_node_foreach(ctx->list, check_current_char, &state);
	}

	//if (r->index == 0)
	//	printf("current == %d\n", state.current);

	if (pstream_close(ps))
	{
		perror("pstream_close");
		pthread_exit(0);
	}

	pthread_exit(r);
}


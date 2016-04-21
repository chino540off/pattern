#include <pstream.h>
#include <pattern.h>
#include <counter.h>

struct map_state_s
{
	bool can_start;
	char c;
	int current;
};
typedef struct map_state_s map_state_t;

//static void print_status(void const * elt, void * data)
//{
//	counter_t * counter = (counter_t *)elt;
//	map_state_t * state = (map_state_t *)data;
//
//	printf(" -- %s seen %d, offset %d\n", counter->pattern, counter->value, counter->offset);
//}

static void check_current_char(void const * elt, void * data)
{
	counter_t * counter = (counter_t *)elt;
	map_state_t * state = (map_state_t *)data;

	if (!state->can_start && counter->offset == 0)
		return;

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
	state.can_start = true;

	if ((ps = pstream_open(ctx->filename, "r", r->index, r->n)) == 0)
	{
		perror("pstream_open");
		pthread_exit(0);
	}

	pstream_seek(ps, 0);

	while (!pstream_eop(ps))
	{
		state.c = pstream_getc(ps);
		slist_node_foreach(ctx->list, check_current_char, &state);
	}

	//printf("Thread[%d] status after end of part\n", r->index);
	//slist_node_foreach(ctx->list, print_status, &state);

	state.can_start = false;

	while (state.current > 0)
	{
		state.c = pstream_getc(ps);
		slist_node_foreach(ctx->list, check_current_char, &state);
	}

	if (pstream_close(ps))
	{
		perror("pstream_close");
		pthread_exit(0);
	}

	pthread_exit(r);
}


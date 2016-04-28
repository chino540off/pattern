#include <pstream.h>
#include <pattern.h>
#include <counter.h>

struct map_state_s
{
	bool can_start;
	int c;
	int current;
};
typedef struct map_state_s map_state_t;

//static void print_status(void const * elt, void * data)
//{
//	counter_t * counter = (counter_t *)elt;
//	map_state_t * state = (map_state_t *)data;
//
//	printf(" -- %s seen %d\n", counter->pattern, counter->value);
//	for (unsigned int pos = counter->size; pos > 0; --pos)
//		printf("pos %d used: %d\n", pos - 1, counter->used[pos - 1]);
//}

static void check_current_char(void const * elt, void * data)
{
	counter_t * counter = (counter_t *)elt;
	map_state_t * state = (map_state_t *)data;

	if (counter->pattern[0] == state->c && state->can_start)
	{
		++state->current;
		counter->used[0] = 1;
	}

	for (unsigned int pos = counter->size; pos > 0; --pos)
	{
		if (counter->used[pos - 1])
		{
			if (counter->pattern[pos - 1] == state->c)
			{
				//printf("pos %d used: %d\n", pos - 1, counter->used[pos - 1]);
				counter->used[pos] = 1;

				if (pos == counter->size)
				{
					--state->current;
					++counter->value;
				}
			}
			else
			{
				--state->current;
			}
		}
		counter->used[pos - 1] = 0;
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
		if (state.c == EOF)
			break;
		slist_foreach(ctx->list, check_current_char, &state);
	}

	//printf("Thread[%d] status after end of part\n", r->index);
	//slist_node_foreach(ctx->list, print_status, &state);

	state.can_start = false;

	while (state.current > 0)
	{
		state.c = pstream_getc(ps);
		if (state.c == EOF)
			break;
		slist_foreach(ctx->list, check_current_char, &state);
	}

	if (pstream_close(ps))
	{
		perror("pstream_close");
		pthread_exit(0);
	}

	pthread_exit(r);
}


#include <pattern.h>
#include <counter.h>

static void add(void const * elt, void * data)
{
	slist_node_t ** p = (slist_node_t **)data;
	counter_t * c_res = (counter_t *)elt;
	counter_t * c_cur = (counter_t *)(*p)->elt;

	c_res->value += c_cur->value;
	*p = (*p)->next;
}

reducer_t * pattern_reduce(reducer_t * r)
{
	pattern_ctx_t * ctx1 = (pattern_ctx_t *)r->ctx1;
	pattern_ctx_t * ctx2 = (pattern_ctx_t *)r->ctx2;

	slist_node_t * p = ctx2->list->head;
	slist_foreach(ctx1->list, add, &p);

	slist_free(ctx2->list);
	ctx2->list = 0;

	pthread_exit(r);
}


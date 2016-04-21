#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <cluster.h>

#define N_CLUSTER 4

struct counter_ctx_s
{
	unsigned int value;
};
typedef struct counter_ctx_s counter_ctx_t;

static mapper_t * map(mapper_t * r)
{
	counter_ctx_t * ctx = (counter_ctx_t *)r->data;

	ctx->value = r->index + 1;

	pthread_exit(r);
}

static reducer_t * reduce(reducer_t * r)
{
	counter_ctx_t * ctx1 = (counter_ctx_t *)r->ctx1;
	counter_ctx_t * ctx2 = (counter_ctx_t *)r->ctx2;

	//sleep(ctx1->value);
	ctx1->value += ctx2->value;

	pthread_exit(r);
}

static unsigned int sum(unsigned int v)
{
	unsigned int res = 0;

	while (v)
		res += v--;

	return res;
}

int main(int argc,
		 char const ** argv)
{
	if (argc < 2)
		return 1;

	unsigned int	n = atoi(argv[1]);
	cluster_t *		cluster;
	counter_ctx_t	contexts[n];
	void *			pcontexts[n];

	for (unsigned int i = 0; i < n; ++i)
	{
		contexts[i].value = 0;
		pcontexts[i] = &contexts[i];
	}

	cluster = cluster_new(n, pcontexts);
	cluster_map(cluster, map);

	for (unsigned int i = 0; i < n; ++i)
	{
		printf("map: %d == %d?\n", contexts[i].value, i + 1);
		assert(contexts[i].value == i + 1);
	}

	counter_ctx_t * res = cluster_reduce(cluster, reduce);

	printf("reduce: %d == %d?\n", res->value, sum(n));
	assert(res->value == sum(n));

	cluster_free(cluster);
}

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <cluster.h>

#define N_CLUSTER 4

struct counter_ctx_s
{
	unsigned int value;
};
typedef struct counter_ctx_s counter_ctx_t;

void no_free(void * p)
{
	p = p;
}

runner_t * r_init(runner_t * r)
{
	counter_ctx_t * ctx = (counter_ctx_t *)r->data;

	ctx->value = r->index;

	pthread_exit(r);
}

int main(int argc,
		 char const ** argv)
{
	if (argc < 3)
		return 1;

	unsigned int	n = N_CLUSTER;
	cluster_t *		cluster;
	counter_ctx_t	contexts[n];
	void *			pcontexts[n];

	for (unsigned int i = 0; i < N_CLUSTER; ++i)
	{
		contexts[i].value = 0;
		pcontexts[i] = &contexts[i];
	}

	cluster = cluster_new(n, pcontexts);
	cluster_map(cluster, r_init);

	for (unsigned int i = 0; i < N_CLUSTER; ++i)
	{
		assert(contexts[i].value == i);
	}

	cluster_free(cluster);
}

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <mapper.h>

#define NMAPPER 4

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

	unsigned int	n = NMAPPER;
	mapper_t *		mapper;
	counter_ctx_t	contexts[n];
	void *			pcontexts[n];

	for (unsigned int i = 0; i < NMAPPER; ++i)
	{
		contexts[i].value = 0;
		pcontexts[i] = &contexts[i];
	}

	mapper = mapper_new(n, pcontexts);
	mapper_run(mapper, r_init);

	for (unsigned int i = 0; i < NMAPPER; ++i)
	{
		assert(contexts[i].value == i);
	}

	mapper_free(mapper);
}

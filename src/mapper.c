#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mapper.h>

mapper_t * mapper_new(unsigned int n, void * contexts[])
{
	mapper_t * mapper = 0;

	if ((mapper = malloc(sizeof (mapper_t))) == 0)
		return 0;

	mapper->n = n;

	if ((mapper->runners = malloc(mapper->n * sizeof (runner_t))) == 0)
	{
		free(mapper);
		return 0;
	}

	for (unsigned int i = 0; i < n; ++i)
	{
		mapper->runners[i].data = contexts[i];
		mapper->runners[i].index = i;
	}

	return mapper;
}

void mapper_free(mapper_t * mapper)
{
	free(mapper->runners);
	free(mapper);
}

void mapper_run(mapper_t * mapper, runner_f doit)
{
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (unsigned int i = 0; i < mapper->n; ++i)
	{
		if (pthread_create(&mapper->runners[i].thread, &attr, doit, mapper->runners + i))
		{
			perror("pthread_create: ");
			return;
		}

	}

	pthread_attr_destroy(&attr);

	for (unsigned int i = 0; i < mapper->n; ++i)
	{
		void * status;

		if (pthread_join(mapper->runners[i].thread, &status))
		{
			perror("pthread_join: ");
		}
	}
}

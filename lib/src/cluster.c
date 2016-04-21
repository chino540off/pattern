#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cluster.h>

cluster_t * cluster_new(unsigned int n, void * contexts[])
{
	cluster_t * cluster = 0;

	if ((cluster = malloc(sizeof (cluster_t))) == 0)
		return 0;

	cluster->n = n;

	if ((cluster->mappers = malloc(cluster->n * sizeof (mapper_t))) == 0)
	{
		free(cluster);
		return 0;
	}

	for (unsigned int i = 0; i < n; ++i)
	{
		cluster->mappers[i].data = contexts[i];
		cluster->mappers[i].index = i;
		cluster->mappers[i].n = n;
	}

	return cluster;
}

void cluster_free(cluster_t * cluster)
{
	free(cluster->mappers);
	free(cluster);
}

void cluster_map(cluster_t * cluster, cluster_map_f mapper)
{
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (unsigned int i = 0; i < cluster->n; ++i)
	{
		if (pthread_create(&cluster->mappers[i].thread, &attr, (void*(*)(void*))mapper, cluster->mappers + i))
		{
			perror("pthread_create: ");
			return;
		}
	}

	pthread_attr_destroy(&attr);

	for (unsigned int i = 0; i < cluster->n; ++i)
	{
		void * status;

		if (pthread_join(cluster->mappers[i].thread, &status))
		{
			perror("pthread_join: ");
		}
	}
}

void * cluster_reduce(cluster_t * cluster, cluster_reduce_f reduce)
{
	unsigned int gap = 1;
	unsigned int limit = cluster->n;
	reducer_t reducers[cluster->n];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (unsigned int i = 0; i < cluster->n; ++i)
	{
		reducers[i].index = i;
		reducers[i].index = cluster->n;
		reducers[i].ctx1 = cluster->mappers[i].data;
	}

	while (gap < limit)
	{
		for (unsigned int i = 0; (i + gap) < cluster->n; i += 2 * gap)
		{
			reducers[i].ctx2 = cluster->mappers[i + gap].data;
			//printf("%d <-- %d\n", i, i + gap);

			if (pthread_create(&reducers[i].thread, &attr, (void*(*)(void*))reduce, reducers + i))
			{
				perror("pthread_create: ");
				return 0;
			}
		}
		//printf("-----------\n");

		for (unsigned int i = 0; (i + gap) < cluster->n; i += 2 * gap)
		{
			void * status;

			//printf("wait for result in %d\n", i);
			if (pthread_join(reducers[i].thread, &status))
			{
				perror("pthread_join: ");
				return 0;
			}
		}

		gap *= 2;
	}

	pthread_attr_destroy(&attr);

	return reducers[0].ctx1;
}

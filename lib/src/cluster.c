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

	if ((cluster->runners = malloc(cluster->n * sizeof (runner_t))) == 0)
	{
		free(cluster);
		return 0;
	}

	for (unsigned int i = 0; i < n; ++i)
	{
		cluster->runners[i].data = contexts[i];
		cluster->runners[i].index = i;
		cluster->runners[i].n = n;
	}

	return cluster;
}

void cluster_free(cluster_t * cluster)
{
	free(cluster->runners);
	free(cluster);
}

void cluster_map(cluster_t * cluster, runner_f mapper)
{
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (unsigned int i = 0; i < cluster->n; ++i)
	{
		if (pthread_create(&cluster->runners[i].thread, &attr, (void*(*)(void*))mapper, cluster->runners + i))
		{
			perror("pthread_create: ");
			return;
		}
	}

	pthread_attr_destroy(&attr);

	for (unsigned int i = 0; i < cluster->n; ++i)
	{
		void * status;

		if (pthread_join(cluster->runners[i].thread, &status))
		{
			perror("pthread_join: ");
		}
	}
}

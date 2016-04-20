#ifndef CLUSTER_H_
# define CLUSTER_H_

# include <pthread.h>

struct runner_s
{
	pthread_t thread;
	unsigned int index;
	unsigned int n;
	void * data;
};
typedef struct runner_s runner_t;

typedef runner_t * (*runner_f)(runner_t *);

struct cluster_s
{
	runner_t * runners;
	unsigned int n;
};
typedef struct cluster_s cluster_t;

/** 
 * @brief Create a new cluster
 * 
 * @param n the number of runners
 * @param contexts an array of contexts given to runners
 * 
 * @return 
 */
cluster_t * cluster_new(unsigned int n, void * contexts[]);

/** 
 * @brief Free a cluster
 * 
 * @param cluster a cluster
 */
void cluster_free(cluster_t * cluster);

/** 
 * @brief Perform mapper method on runners
 * 
 * @param cluster a cluster
 * @param mapper method to be performed
 */
void cluster_map(cluster_t * cluster, runner_f mapper);

#endif /** !CLUSTER_H_  */


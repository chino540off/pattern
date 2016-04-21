#ifndef CLUSTER_H_
# define CLUSTER_H_

# include <pthread.h>

struct mapper_s
{
	pthread_t thread;
	unsigned int index;
	unsigned int n;
	void * data;
};
typedef struct mapper_s mapper_t;
typedef mapper_t * (*cluster_map_f)(mapper_t *);

struct reducer_s
{
	pthread_t thread;
	unsigned int index;
	unsigned int n;
	void * ctx1;
	void * ctx2;
};
typedef struct reducer_s reducer_t;
typedef reducer_t * (*cluster_reduce_f)(reducer_t *);

struct cluster_s
{
	mapper_t * mappers;
	unsigned int n;
};
typedef struct cluster_s cluster_t;

/** 
 * @brief Create a new cluster
 * 
 * @param n the number of mappers and reducers
 * @param contexts an array of contexts given to mappers
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
 * @brief Perform mapper method on mappers
 * 
 * @param cluster a cluster
 * @param mapper method to be performed
 */
void cluster_map(cluster_t * cluster, cluster_map_f mapper);

/** 
 * @brief Perform reduce method on reducers
 * 
 * @param cluster a cluster
 * @param reduce method to be performed
 * 
 * @return result (the data of the first reducers)
 */
void * cluster_reduce(cluster_t * cluster, cluster_reduce_f reduce);

#endif /** !CLUSTER_H_  */


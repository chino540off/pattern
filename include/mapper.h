#ifndef MAPPER_H_
# define MAPPER_H_

# include <list.h>
# include <pthread.h>

struct runner_s
{
	pthread_t thread;
	unsigned int index;
	void * data;
};
typedef struct runner_s runner_t;

typedef void * (*runner_f)(void *);

struct mapper_s
{
	runner_t * runners;
	unsigned int n;
};
typedef struct mapper_s mapper_t;

/** 
 * @brief 
 * 
 * @param n
 * @param patterns[]
 * 
 * @return 
 */
mapper_t * mapper_new(unsigned int n, void * contexts[]);

/** 
 * @brief 
 * 
 * @param mapper
 */
void mapper_free(mapper_t * mapper);

/** 
 * @brief 
 * 
 * @param mapper
 */
void mapper_run(mapper_t * mapper, runner_f doit);

#endif /** !MAPPER_H_  */


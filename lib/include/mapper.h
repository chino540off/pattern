#ifndef MAPPER_H_
# define MAPPER_H_

# include <list.h>
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

struct mapper_s
{
	runner_t * runners;
	unsigned int n;
};
typedef struct mapper_s mapper_t;

/** 
 * @brief Create a new mapper
 * 
 * @param n the number of runners
 * @param contexts an array of contexts given to runners
 * 
 * @return 
 */
mapper_t * mapper_new(unsigned int n, void * contexts[]);

/** 
 * @brief Free a mapper
 * 
 * @param mapper a mapper
 */
void mapper_free(mapper_t * mapper);

/** 
 * @brief Perform a method on runners
 * 
 * @param mapper a mapper
 * @param doit a method to be performed
 */
void mapper_run(mapper_t * mapper, runner_f doit);

#endif /** !MAPPER_H_  */


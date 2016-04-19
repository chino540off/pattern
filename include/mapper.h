#ifndef MAPPER_H_
# define MAPPER_H_

# include <list.h>

struct runner_s
{
	list_node_t * list;
};
typedef struct runner_s runner_t;

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
mapper_t * mapper_new(unsigned int n, char const * patterns[]);

/** 
 * @brief 
 * 
 * @param mapper
 */
void mapper_free(mapper_t * mapper);

#endif /** !MAPPER_H_  */


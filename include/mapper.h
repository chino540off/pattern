#ifndef MAPPER_H_
# define MAPPER_H_

# include <list.h>

struct mapper_s
{
	list_node_t** arr;
	unsigned int n;
};

typedef struct mapper_s mapper_t;

/** 
 * @brief 
 * 
 * @param len
 * @param argv[]
 * 
 * @return 
 */
mapper_t * mapper_new(unsigned int len, char const * argv[]);

/** 
 * @brief 
 * 
 * @param mapper
 */
void mapper_free(mapper_t * mapper);

#endif /** !MAPPER_H_  */


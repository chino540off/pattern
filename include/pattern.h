#ifndef PATTERN_H_
# define PATTERN_H_

# include <slist.h>
# include <cluster.h>

struct pattern_ctx_s
{
	slist_node_t * list;
	char const * filename;
};
typedef struct pattern_ctx_s pattern_ctx_t;

/** 
 * @brief 
 * 
 * @param r
 * 
 * @return 
 */
runner_t * pattern_map(runner_t * r);

#endif /** !PATTERN_H_  */


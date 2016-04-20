#ifndef SLIST_H_
# define SLIST_H_

struct slist_node_s
{
	struct slist_node_s * next;
	void * elt;
};
typedef struct slist_node_s slist_node_t;

typedef int (*slist_node_t_cmp_f)(void const *, void const *);
typedef void (*slist_node_t_foreach_f)(void const *, void *);
typedef void * (*slist_node_t_dup_f)(void const *);
typedef void (*slist_node_t_free_f)(void *);

/** 
 * @brief Create a new list node
 * 
 * @param elt the element in the node
 * @param next the next in the linkage
 * 
 * @return the new element or null if there is no enough memory
 */
slist_node_t * slist_node_new(void * elt, slist_node_t * next);

/** 
 * @brief Linked List insertion
 * 
 * @param h head list
 * @param elt element to be inserted
 * @param cmp comparaison method
 * 
 * @return the new head of the list
 */
slist_node_t * slist_node_insert(slist_node_t * h, void * elt, slist_node_t_cmp_f cmp);

/** 
 * @brief Iter on each elements
 * 
 * @param h the head of the list
 * @param f the method to applied on each element
 * @param data a data given by the client
 */
void slist_node_foreach(slist_node_t const * h, slist_node_t_foreach_f f, void * data);

/** 
 * @brief Duplicate each elements of the list
 * 
 * @param h the head of the list
 * @param elt_dup the element duplication policy
 * 
 * @return a new list
 */
slist_node_t * slist_node_dup(slist_node_t const * h, slist_node_t_dup_f elt_dup);

/** 
 * @brief Free each elements of the list
 * 
 * @param h the head of the list
 * @param elt_free the element free policy
 */
void slist_node_free(slist_node_t * h, slist_node_t_free_f elt_free);

#endif /** !SLIST_H_  */


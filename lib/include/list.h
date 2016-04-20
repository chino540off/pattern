#ifndef LIST_H_
# define LIST_H_

struct list_node_s
{
	struct list_node_s * next;
	void * elt;
};
typedef struct list_node_s list_node_t;

typedef int (*list_t_cmp_f)(void const *, void const *);
typedef void (*list_t_foreach_f)(void const *, void *);
typedef void * (*list_t_dup_f)(void const *);
typedef void (*list_t_free_f)(void *);

/** 
 * @brief Create a new list node
 * 
 * @param elt the element in the node
 * @param next the next in the linkage
 * 
 * @return the new element or null if there is no enough memory
 */
list_node_t * list_node_new(void * elt, list_node_t * next);

/** 
 * @brief Linked List insertion
 * 
 * @param h head list
 * @param elt element to be inserted
 * @param cmp comparaison method
 * 
 * @return the new head of the list
 */
list_node_t * list_node_insert(list_node_t * h, void * elt, list_t_cmp_f cmp);

/** 
 * @brief Iter on each elements
 * 
 * @param h the head of the list
 * @param f the method to applied on each element
 * @param data a data given by the client
 */
void list_node_foreach(list_node_t const * h, list_t_foreach_f f, void * data);

/** 
 * @brief Duplicate each elements of the list
 * 
 * @param h the head of the list
 * @param elt_dup the element duplication policy
 * 
 * @return a new list
 */
list_node_t * list_node_dup(list_node_t const * h, list_t_dup_f elt_dup);

/** 
 * @brief Free each elements of the list
 * 
 * @param h the head of the list
 * @param elt_free the element free policy
 */
void list_node_free(list_node_t * h, list_t_free_f elt_free);

#endif /** !LIST_H_  */


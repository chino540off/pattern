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

struct slist_s
{
	struct slist_node_s * head;

	slist_node_t_free_f free;
	slist_node_t_dup_f dup;
	slist_node_t_cmp_f cmp;
};
typedef struct slist_s slist_t;

/** 
 * @brief Create a new list
 * 
 * @param free the element free policy
 * @param dup the element duplication policy
 * @param cmp the element comparaison policy
 * 
 * @return the new list or null if there is no enough memory
 */
slist_t * slist_new(slist_node_t_free_f free, slist_node_t_dup_f dup, slist_node_t_cmp_f cmp);

/** 
 * @brief Linked List insertion
 * 
 * @param l the list
 * @param elt element to be inserted
 * 
 * @return the new head of the list
 */
slist_t * slist_insert(slist_t * l, void * elt);

/** 
 * @brief Iter on each elements
 * 
 * @param l the list
 * @param f the method to applied on each element
 * @param data a data given by the client
 */
void slist_foreach(slist_t const * l, slist_node_t_foreach_f f, void * data);

/** 
 * @brief Duplicate each elements of the list
 * 
 * @param l the list
 * 
 * @return a new list
 */
slist_t * slist_dup(slist_t const * l);

/** 
 * @brief Free each elements of the list
 * 
 * @param l the list
 */
void slist_free(slist_t * l);

#endif /** !SLIST_H_  */


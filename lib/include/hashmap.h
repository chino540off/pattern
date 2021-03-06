#ifndef HASHMAP_H_
# define HASHMAP_H_

enum hashmap_cerr_e
{
	MAP_MISSING = -3,
	MAP_FULL = -2,
	MAP_OMEM = -1,
	MAP_OK = 0,
};
typedef enum hashmap_cerr_e hashmap_cerr_t;

/* We need to keep keys and values */
struct hashmap_node_s
{
	char * key;
	int in_use;
	void * value;
};
typedef struct hashmap_node_s hashmap_node_t;

struct hashmap_s
{
	unsigned int table_size;
	unsigned int size;
	hashmap_node_t * entries;
};
typedef struct hashmap_s hashmap_t;

typedef void (*hashmap_node_t_foreach_f)(void const *, void *);

/** 
 * @brief Create a new hashmap
 * 
 * @return an empty hashmap. Returns NULL if empty.
 */
hashmap_t * hashmap_new();

/*
 * Iteratively call f with argument (item, data) for
 * each element data in the hashmap. The function must
 * return a map status code. If it returns anything other
 * than MAP_OK the traversal is terminated. f must
 * not reenter any hashmap functions, or deadlock may arise.
 */
hashmap_cerr_t hashmap_foreach(hashmap_t const * m, hashmap_node_t_foreach_f f, void * item);

/*
 * Add an element to the hashmap. Return MAP_OK or MAP_OMEM.
 */
hashmap_cerr_t hashmap_put(hashmap_t * m, char * key, void * value);

/*
 * Get an element from the hashmap. Return MAP_OK or MAP_MISSING.
 */
hashmap_cerr_t hashmap_get(hashmap_t const * m, char const * key, void ** arg);

/*
 * Remove an element from the hashmap. Return MAP_OK or MAP_MISSING.
 */
hashmap_cerr_t hashmap_remove(hashmap_t * m, char const * key);

/*
 * Free the hashmap
 */
void hashmap_free(hashmap_t * m);

/*
 * Get the current size of a hashmap
 */
unsigned int hashmap_length(hashmap_t const * m);

#endif /** !HASHMAP_H_  */


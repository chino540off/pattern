#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hashmap.h"

#define KEY_MAX_LENGTH 256
#define KEY_PREFIX "somekey"
#define KEY_COUNT 1024 * 1024

struct data_struct_s
{
    char key_string[KEY_MAX_LENGTH];
    int number;
};
typedef struct data_struct_s data_struct_t;

void hashmap_node_print(void const * value, void * data)
{
	FILE * s = (FILE *)data;
	data_struct_t * v = (data_struct_t *)value;

	fprintf(s, "%s %d\n", v->key_string, v->number);
}

int main(void)
{
	int error;
	hashmap_t * mymap;
	char key_string[KEY_MAX_LENGTH];
	data_struct_t* value;

	mymap = hashmap_new();

	/* First, populate the hash map with ascending values */
	for (int index = 0; index < KEY_COUNT; ++index)
	{
		/* Store the key string along side the numerical value so we can free it later */
		value = malloc(sizeof (data_struct_t));
		snprintf(value->key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
		value->number = index;

		error = hashmap_put(mymap, value->key_string, value);
		assert(error == MAP_OK);
	}

	hashmap_foreach(mymap, hashmap_node_print, stdout);

	/* Now, check all of the expected values are there */
	for (int index = 0; index < KEY_COUNT; ++index)
	{
		snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);

		error = hashmap_get(mymap, key_string, (void**)(&value));

		/* Make sure the value was both found and the correct number */
		assert(error == MAP_OK);
		assert(value->number==index);
	}

	/* Make sure that a value that wasn't in the map can't be found */
	snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, KEY_COUNT);

	error = hashmap_get(mymap, key_string, (void**)(&value));

	/* Make sure the value was not found */
	assert(error == MAP_MISSING);

	/* Free all of the values we allocated and remove them from the map */
	for (int index = 0; index < KEY_COUNT; ++index)
	{
		snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);

		error = hashmap_get(mymap, key_string, (void**)(&value));
		assert(error == MAP_OK);

		error = hashmap_remove(mymap, key_string);
		assert(error == MAP_OK);

		free(value);
	}

	/* Now, destroy the map */
	hashmap_free(mymap);

	return 0;
}

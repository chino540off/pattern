#include <stdio.h>
#include <string.h>

#include <list.h>
#include <counter.h>

struct lines_s
{
	list_node_t** arr;
	unsigned int len;
};

typedef struct lines_s lines_t;

int c_cmp(void const * a, void const * b)
{
	return strcmp(((counter_t const *)a)->pattern, ((counter_t const *)b)->pattern);
}

void * c_dup(void const * elt)
{
	return counter_dup((counter_t const *)elt);
}

void c_print(void const * a, void * data)
{
	FILE * s = (FILE *)data;
	counter_print((counter_t const *)a, s);
	fprintf(s, "\n");
}

void c_free(void * elt)
{
	counter_free((counter_t *)elt);
}

lines_t * lines_new(unsigned int len, char const * argv[])
{
	lines_t * lines = 0;

	if ((lines = malloc(sizeof (lines_t))) == 0)
		return 0;

	lines->len = len;

	if ((lines->arr = malloc(lines->len * sizeof (list_node_t*))) == 0)
	{
		free(lines);
		return 0;
	}

	for (unsigned int i = 0; argv[i]; ++i)
		lines->arr[0] = list_node_insert(lines->arr[0], counter_new(0, argv[i]), c_cmp);

	for (unsigned int i = 1; i < len; ++i)
		lines->arr[i] = list_node_dup(lines->arr[0], c_dup);

	return lines;
}

void lines_free(lines_t * lines)
{
	for (unsigned int i = 0; i < lines->len; ++i)
		list_node_free(lines->arr[i], c_free);

	free(lines->arr);
	free(lines);
}

int main(int argc,
		 char const ** argv)
{
	if (argc < 3)
		return 1;

	unsigned int	len = atoi(argv[1]);
	lines_t *		lines;

	lines = lines_new(len, argv + 2);

	for (unsigned int i = 0; i < lines->len; ++i)
	{
		list_node_foreach(lines->arr[i], c_print, stdout);
		fprintf(stdout, "\n");
	}

	lines_free(lines);
}

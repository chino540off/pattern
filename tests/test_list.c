#include <string.h>
#include <stdio.h>

#include <list.h>

int cmp(void const * a, void const * b)
{
	return strcmp((char const *)a, (char const *)b);
}

void print(void const * a, void * data)
{
	data = data;
	a = a;
}

void * no_dup(void const * elt)
{
	return (void *)elt;
}

void no_free(void * elt)
{
	elt = elt;
}

int main()
{
	char const * tab[] = {
		"toto",
		"ab",
		"tata",
		"aa",
	};

	list_node_t * l = 0;

	for (unsigned int i = 0; i < (sizeof (tab) / sizeof (char const *)); ++i)
		l = list_node_insert(l, (void *)tab[i], cmp);

	list_node_foreach(l, print, 0);

	list_node_t * d1 = list_node_dup(l, no_dup);
	list_node_t * d2 = list_node_dup(l, no_dup);
	list_node_t * d3 = list_node_dup(l, no_dup);

	list_node_foreach(d1, print, 0);
	list_node_foreach(d2, print, 0);
	list_node_foreach(d3, print, 0);

	list_node_free(d1, no_free);
	list_node_free(d2, no_free);
	list_node_free(d3, no_free);
	list_node_free(l,  no_free);
}

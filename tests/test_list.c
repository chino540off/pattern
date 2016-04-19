#include <string.h>
#include <stdio.h>
#include <assert.h>

#include <list.h>

int cmp(void const * a, void const * b)
{
	return strcmp((char const *)a, (char const *)b);
}

void count(void const * a, void * data)
{
	unsigned int * cpt =(unsigned int *)data;
	a = a;

	++(*cpt);
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
	char const * tab[] =
	{
		"toto",
		"ab",
		"tata",
		"aa",
	};

	list_node_t * l = 0;

	for (unsigned int i = 0; i < (sizeof (tab) / sizeof (char const *)); ++i)
		l = list_node_insert(l, (void *)tab[i], cmp);

	assert(l);

	unsigned int cpt = 0;
	list_node_foreach(l, count, &cpt);
	assert(cpt == 4);

	cpt = 0;
	list_node_t * d1 = list_node_dup(l, no_dup);
	assert(d1);

	list_node_foreach(d1, count, &cpt);
	assert(cpt == 4);

	list_node_free(d1, no_free);
	list_node_free(l,  no_free);
}

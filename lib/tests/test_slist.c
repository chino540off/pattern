#include <string.h>
#include <stdio.h>
#include <assert.h>

#include <slist.h>

static int cmp(void const * a, void const * b)
{
	return strcmp((char const *)a, (char const *)b);
}

static void count(void const * a, void * data)
{
	unsigned int * cpt =(unsigned int *)data;

	(void)(a);

	++(*cpt);
}

static void * no_dup(void const * elt)
{
	return (void *)elt;
}

static void no_free(void * elt)
{
	(void)(elt);
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

	slist_t * l = slist_new(no_free, no_dup, cmp);

	for (unsigned int i = 0; i < (sizeof (tab) / sizeof (char const *)); ++i)
		l = slist_insert(l, (void *)tab[i]);

	assert(l);

	unsigned int cpt = 0;
	slist_foreach(l, count, &cpt);
	assert(cpt == 4);

	cpt = 0;
	slist_t * d1 = slist_dup(l);
	assert(d1);

	slist_foreach(d1, count, &cpt);
	assert(cpt == 4);

	slist_free(d1);
	slist_free(l);
}

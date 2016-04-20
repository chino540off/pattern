#include <stdlib.h>

#include <slist.h>

slist_node_t * slist_node_new(void * elt, slist_node_t * next)
{
	slist_node_t * p = 0;

	if ((p = malloc(sizeof (slist_node_t))) == 0)
	{
		return 0;
	}

	p->elt = elt;
	p->next = next;

	return p;
}

slist_node_t * slist_node_insert(slist_node_t * h, void * elt, slist_node_t_cmp_f cmp)
{
	if (h == 0)
	{
		h = slist_node_new(elt, 0);
	}
	else
	{
		slist_node_t * p = h;
		slist_node_t * prev = 0;

		while (p && cmp(elt, p->elt) >= 0)
		{
			prev = p;
			p = p->next;
		}

		if (prev == 0) /// Head insertion
		{
			h = slist_node_new(elt, p);
		}
		else /// Insertion
		{
			prev->next = slist_node_new(elt, p);
		}
	}

	return h;
}

void slist_node_foreach(slist_node_t const * h, slist_node_t_foreach_f f, void * data)
{
	slist_node_t const * p = h;

	while (p)
	{
		f(p->elt, data);
		p = p->next;
	}
}

slist_node_t * slist_node_dup(slist_node_t const * h, slist_node_t_dup_f elt_dup)
{
	slist_node_t * new_h = 0;

	if (h)
	{
		slist_node_t ** new_p = &new_h;
		slist_node_t const * p = h;

		while (p)
		{
			*new_p = slist_node_new(elt_dup(p->elt), 0);
			p = p->next;
			new_p = &((*new_p)->next);
		}
	}

	return new_h;
}

void slist_node_free(slist_node_t * h, slist_node_t_free_f elt_free)
{
	while (h)
	{
		slist_node_t * t = h;
		h = h->next;

		elt_free(t->elt);
		free(t);

	}
}


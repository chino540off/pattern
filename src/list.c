#include <list.h>

list_node_t * list_node_new(void * elt, list_node_t * next)
{
	list_node_t * p = 0;

	if ((p = malloc(sizeof (list_node_t))) == 0)
	{
		return 0;
	}

	p->elt = elt;
	p->next = next;

	return p;
}

list_node_t * list_node_insert(list_node_t * h, void * elt, list_t_cmp_f cmp)
{
	if (h == 0)
	{
		h = list_node_new(elt, 0);
	}
	else
	{
		list_node_t * p = h;
		list_node_t * prev = 0;

		while (p && cmp(elt, p->elt) >= 0)
		{
			prev = p;
			p = p->next;
		}

		if (prev == 0) /// Head insertion
		{
			h = list_node_new(elt, p);
		}
		else /// Insertion
		{
			prev->next = list_node_new(elt, p);
		}
	}

	return h;
}

void list_node_foreach(list_node_t const * h, list_t_foreach_f f, void * data)
{
	list_node_t const * p = h;

	while (p)
	{
		f(p->elt, data);
		p = p->next;
	}
}

list_node_t * list_node_dup(list_node_t const * h, list_t_dup_f elt_dup)
{
	list_node_t * new_h = 0;

	if (h)
	{
		list_node_t ** new_p = &new_h;
		list_node_t const * p = h;

		while (p)
		{
			*new_p = list_node_new(elt_dup(p->elt), 0);
			p = p->next;
			new_p = &((*new_p)->next);
		}
	}

	return new_h;
}

void list_node_free(list_node_t * h, list_t_free_f elt_free)
{
	while (h)
	{
		list_node_t * t = h;
		h = h->next;

		elt_free(t->elt);
		free(t);

	}
}


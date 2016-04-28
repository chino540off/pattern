#include <stdlib.h>

#include <slist.h>

static slist_node_t * slist_node_new(void * elt, slist_node_t * next)
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

slist_t * slist_new(slist_node_t_free_f free, slist_node_t_dup_f dup, slist_node_t_cmp_f cmp)
{
	slist_t * l = 0;

	if ((l = malloc(sizeof (slist_t))) == 0)
	{
		return 0;
	}

	l->head = 0;
	l->free = free;
	l->dup = dup;
	l->cmp = cmp;

	return l;
}

slist_t * slist_insert(slist_t * l, void * elt)
{
	if (l->head == 0)
	{
		l->head = slist_node_new(elt, 0);
	}
	else
	{
		slist_node_t * p = l->head;
		slist_node_t * prev = 0;

		while (p && l->cmp(elt, p->elt) >= 0)
		{
			prev = p;
			p = p->next;
		}

		if (prev == 0) /// Head insertion
		{
			l->head = slist_node_new(elt, p);
		}
		else /// Insertion
		{
			prev->next = slist_node_new(elt, p);
		}
	}

	return l;
}

void slist_foreach(slist_t const * l, slist_node_t_foreach_f f, void * data)
{
	slist_node_t const * p = l->head;

	while (p)
	{
		f(p->elt, data);
		p = p->next;
	}
}

slist_t * slist_dup(slist_t const * l)
{
	slist_t * new_l = slist_new(l->free, l->dup, l->cmp);

	if (new_l == 0)
		return 0;

	if (l->head)
	{
		slist_node_t ** new_p = &new_l->head;
		slist_node_t const * p = l->head;

		while (p)
		{
			*new_p = slist_node_new(l->dup(p->elt), 0);
			p = p->next;
			new_p = &((*new_p)->next);
		}
	}

	return new_l;
}

void slist_free(slist_t * l)
{
	while (l->head)
	{
		slist_node_t * t = l->head;
		l->head = l->head->next;

		l->free(t->elt);
		free(t);
	}
	free(l);
}


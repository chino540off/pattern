#include <part_stream.h>

part_stream_t * part_stream_open(char const * fn, char const * m, unsigned int const i, unsigned int const n)
{
	part_stream_t * ps;

	if ((ps = malloc(sizeof (part_stream_t))) == 0)
	{
		return 0;
	}

	if ((ps->fd = fopen(fn, m)) == 0)
	{
		free(ps);
		return 0;
	}

	fseek(ps->fd, 0, SEEK_END);
	unsigned int f_size = ftell(ps->fd);

	ps->slice = f_size / n;
	ps->size = (i == n - 1) ? ps->slice + (f_size % n) : ps->slice;
	ps->offset = 0;
	ps->i = i;
	ps->n = n;

	return ps;
}


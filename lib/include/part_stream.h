#ifndef PART_STREAM_H_
# define PART_STREAM_H_

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

struct part_stream_s
{
	FILE * fd;
	int offset;
	unsigned int size;
	unsigned int slice;
	unsigned int i;
	unsigned int n;
};
typedef struct part_stream_s part_stream_t;

/** 
 * @brief 
 * 
 * @param fn
 * @param m
 * @param i
 * @param n
 * 
 * @return 
 */
part_stream_t * part_stream_open(char const * fn, char const * m, unsigned int const i, unsigned int const n);

/** 
 * @brief 
 * 
 * @param ps
 * 
 * @return 
 */
static inline bool part_stream_eop(part_stream_t const * ps)
{
	return ps->offset >= ps->size;
}

/** 
 * @brief 
 * 
 * @param ps
 * 
 * @return 
 */
static inline char part_stream_getc(part_stream_t * ps)
{
	++ps->offset;
	return fgetc(ps->fd);
}

/** 
 * @brief 
 * 
 * @param ps
 * @param offset
 * 
 * @return 
 */
static inline int part_stream_seek(part_stream_t * ps, int offset)
{
	return fseek(ps->fd, ps->slice * ps->i + offset, SEEK_SET);
}

/** 
 * @brief 
 * 
 * @param ps
 * 
 * @return 
 */
static inline int part_stream_close(part_stream_t * ps)
{
	int ret = fclose(ps->fd);
	free(ps);
	return ret;
}

#endif /** !PART_STREAM_H_  */


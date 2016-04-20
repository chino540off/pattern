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
 * @brief Open a new part stream
 * 
 * @param fn the file to be opened
 * @param m the opened mode
 * @param i the index part
 * @param n the total number of parts
 * 
 * @return a part stream
 */
part_stream_t * part_stream_open(char const * fn, char const * m, unsigned int const i, unsigned int const n);

/** 
 * @brief End Of Part
 * 
 * @param ps a part stream
 * 
 * @return true if it is the end of the part
 */
static inline bool part_stream_eop(part_stream_t const * ps)
{
	return ps->offset >= ps->size;
}

/** 
 * @brief Get the next char in the stream
 * 
 * @param ps a part stream
 * 
 * @return a char
 */
static inline char part_stream_getc(part_stream_t * ps)
{
	++ps->offset;
	return fgetc(ps->fd);
}

/** 
 * @brief Seek into a part stream
 * 
 * @param ps a part stream
 * @param offset seek offset, relative to the index part in the file
 * 
 * @return fseek status
 */
static inline int part_stream_seek(part_stream_t * ps, int offset)
{
	return fseek(ps->fd, ps->slice * ps->i + offset, SEEK_SET);
}

/** 
 * @brief Close a part stream
 * 
 * @param ps a part stream
 * 
 * @return fclose status
 */
static inline int part_stream_close(part_stream_t * ps)
{
	int ret = fclose(ps->fd);
	free(ps);
	return ret;
}

#endif /** !PART_STREAM_H_  */


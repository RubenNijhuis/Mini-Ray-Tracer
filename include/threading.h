/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threading.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 13:08:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/08 19:17:28 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADING_H
# define THREADING_H

# include "bonus.h"

/* TODO: runtime check. */
# if BONUS

#  define N_THREADS (4)

#  define BLOCK_SIZE (64)

#  include <stdint.h> /* uint32_t */
#  include <pthread.h>

typedef struct pixel_block
{
	uint32_t	*pixel_buf;
	uint32_t	x;
	uint32_t	y;
	uint32_t	width;
	uint32_t	height;
}	t_block;

typedef struct s_renderer
{
	pthread_t		threads[N_THREADS];
	pthread_mutex_t	sched_mutex;
	pthread_mutex_t	mlx_mutex;
	uint32_t		x;
	uint32_t		y;
}	t_renderer;

# endif

#endif

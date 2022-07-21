/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threading.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 13:08:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/07/21 16:21:18 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADING_H
# define THREADING_H

// IDEA: have this detect automatically during runtime.
# ifndef N_THREADS
#  define N_THREADS (4)
# endif

# define BLOCK_SIZE (256)

# include "minirt.h"

# include <stdint.h>

# include "bonus.h"

# if BONUS
#  include <pthread.h>
#  include <semaphore.h>
# endif

typedef struct s_block
{
	uint32_t	*pixel_buf;
	uint32_t	x;
	uint32_t	y;
	uint32_t	width;
	uint32_t	height;
}	t_block;

# if BONUS

#  define MSEM_NAME "render_trig_sem"

typedef struct s_renderer
{
	t_program_data	*pd;
	pthread_t		threads[N_THREADS];
	pthread_mutex_t	sched_mutex;
	sem_t			*render_trig_sem;
	t_block			*block_to_render;
	uint32_t		x;
	uint32_t		y;
	int				id_finished;
}	t_renderer;

typedef struct s_routine_args
{
	t_renderer	*renderer;
	int			index;
}	t_routine_args;

void		*child_routine(void *arg);
void		parent_loop(t_renderer *ren, t_routine_args *r);

# endif

// blocks
uint32_t	*create_block_buffer(void);
void		render_block(t_block *block, t_scene *scene);
void		put_block(t_block *block, t_program_data *pd);
void		update_block(t_block *block, uint32_t px, uint32_t py);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_routines.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/09 17:37:01 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/10 13:21:56 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

#if BONUS

# include "threading.h"

# include <stdlib.h> // free

static void	update_render_coords(t_renderer *ren)
{
	ren->x += BLOCK_SIZE;
	if (ren->x >= WIN_WIDTH)
	{
		ren->x = 0;
		ren->y += BLOCK_SIZE;
	}
}

// the main loop. Gets a block to render, renders it, and signals the main
// thread to display it on the screen.
static void	child_inner(t_renderer *ren, t_block *block)
{
	bool	should_stop;

	should_stop = 0;
	while (!should_stop)
	{
		pthread_mutex_lock(&ren->sched_mutex);
		update_block(block, ren->x, ren->y);
		update_render_coords(ren);
		should_stop = (ren->y >= WIN_HEIGHT);
		pthread_mutex_unlock(&ren->sched_mutex);
		render_block(block, &ren->pd->scene);
		pthread_mutex_lock(&ren->sched_mutex);
		ren->block_to_render = block;
		sem_post(ren->render_trig_sem);
	}
}

// a child routine, which renders blocks. At the end, it's signaled
// to the parent it's done.
void	*child_routine(void *arg)
{
	t_renderer	*ren;
	t_block		block;
	int			index;

	ren = ((t_routine_args *)arg)->renderer;
	index = ((t_routine_args *)arg)->index;
	block.pixel_buf = create_block_buffer();
	child_inner(ren, &block);
	pthread_mutex_lock(&ren->sched_mutex);
	ren->id_finished = index;
	sem_post(ren->render_trig_sem);
	free(block.pixel_buf);
	return (NULL);
}

// checks wether all children are finished. Also sets which thread
// is finished.
static bool	parent_loop_check_threads_finished(t_renderer *ren,
	t_routine_args *r)
{
	int		i;
	bool	should_stop;

	r[ren->id_finished].index = -1;
	ren->id_finished = -1;
	i = 0;
	while (i < N_THREADS)
	{
		if (r[i].index != -1)
		{
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&ren->sched_mutex);
	should_stop = (i == N_THREADS);
	return (should_stop);
}

// loop of the parent/main thread. just waits for a signal(from sem) to
// render a block. Exits when every thread is done.
// it's kind of slow to have the main thread render one block at the time
// it inhibits other blocks which are finishing from continuing to render
// the next block. better would be some kind of queue.
void	parent_loop(t_renderer *ren, t_routine_args *r)
{
	while (true)
	{
		sem_wait(ren->render_trig_sem);
		if (ren->id_finished == -1)
		{
			put_block(ren->block_to_render, ren->pd);
			pthread_mutex_unlock(&ren->sched_mutex);
			mlx_force_draw(ren->pd->mlx);
		}
		else
		{
			if (parent_loop_check_threads_finished(ren, r))
			{
				break ;
			}
		}
	}
}

#endif

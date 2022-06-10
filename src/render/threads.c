/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 12:50:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/10 17:51:53 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

#if BONUS

# include "threading.h"
# include "minirt.h"

static void	render_init(t_renderer *ren, t_program_data *pd)
{
	ren->x = 0;
	ren->y = 0;
	ren->pd = pd;
	ren->id_finished = -1;
	if (pthread_mutex_init(&ren->sched_mutex, NULL) == -1)
	{
		exit_perror("mutex init failure");
	}
	ren->render_trig_sem = sem_open(MSEM_NAME, O_CREAT | O_EXCL, 0600, 0);
	if (ren->render_trig_sem == NULL)
	{
		exit_perror("opening sem " MSEM_NAME " failed");
	}
	if (sem_unlink(MSEM_NAME) == -1)
	{
		exit_perror("sem_unlink");
	}
}

void	render(t_program_data *pd)
{
	t_renderer		ren;
	t_routine_args	r[N_THREADS];
	int				i;

	render_init(&ren, pd);
	i = 0;
	while (i < N_THREADS)
	{
		r[i].renderer = &ren;
		r[i].index = i;
		if (pthread_create(&ren.threads[i], NULL, &child_routine, &r[i]) == -1)
			exit_perror("pthread_create");
		i++;
	}
	i = 0;
	while (i < N_THREADS)
	{
		if (pthread_detach(ren.threads[i]) == -1)
			exit_perror("pthread_detach");
		i++;
	}
	parent_loop(&ren, r);
	if (pthread_mutex_destroy(&ren.sched_mutex) == -1)
		exit_perror("mutex destroy");
}

#endif

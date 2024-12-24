/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:13:01 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/24 15:32:40 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_management.h"
#include "../error_management/error_management.h"

void	wait_for_threads(t_scene *scene)
{
	int i;

	i = 0;
	while (i < THREADS)
	{
		if (pthread_join(scene->threads[i].self, NULL))
		{
			return (exit_err(ERR_MEM_MSG, "(malloc)", 2));
		}
		i++;
	}
}

static void	set_thread_backup(t_thread *thread, t_thread_backup *back_up)
{
	thread->current_y = back_up->current_y;
	thread->iterations = back_up->iterations;
}

static void	set_thread_default(t_thread *thread)
{
	thread->current_y = 0;
	thread->iterations = 1;
}

void	set_thread(t_thread *thread, t_thread_backup *back_up, bool do_backup)
{
	if (do_backup)
	{
		set_thread_backup(thread, back_up);
	}
	else
	{
		set_thread_default(thread);		
	}
	thread->y_start = 0;
	thread->y_end = thread->scene->height;
	thread->current_x = 0;
	thread->x_start = thread->id;
	thread->x_end = thread->scene->width;
	thread->x_increment = THREADS;
	thread->pix_rendered = 0;
	thread->time_hit = 0;
	thread->state = malloc(sizeof(uint32_t));
	if (!thread->state)
	{
		return (exit_err(ERR_MEM_MSG, "(malloc)", 2));
	}
	*(thread->state) = mlx_get_time() * (thread->id + 1) * 123456;
}

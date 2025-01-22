/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:44:57 by vpf               #+#    #+#             */
/*   Updated: 2025/01/22 14:55:47 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/modes/edit_mode/edit_mode.h"
#include "path_tracer/modes/render_mode/render_mode.h"
#include "path_tracer/thread_management/thread_management.h"
#include <stdio.h>
#include <stdlib.h>

static void	free_and_backup_thread(t_thread *th)
{
	if (get_stop_status(th->scene) == true)
	{
		th->scene->threads_backup[th->id].iterations = th->iterations - 1;
		th->scene->threads_backup[th->id].current_y = th->current_y;
	}
	free(th->state);
}

static void	*set_rendering(void *args)
{
	t_thread	*th;

	th = args;
	while (get_stop_status(th->scene) == false)
	{
		if (th->current_y >= th->y_end)
			th->current_y = th->y_start;
		while (get_stop_status(th->scene) == false && th->current_y < th->y_end)
		{
			th->current_x = th->x_start;
			while (th->current_x < th->x_end)
			{
				if (th->scene->edit_mode == true)
					edit_mode(th, th->current_x, th->current_y);
				else
					render_mode(th, th->current_x, th->current_y);
				th->current_x += th->x_increment;
			}
			th->current_y++;
		}
		fprintf(stderr, "THREAD: %i || LAP: %i\r", th->id, th->iterations);
		th->iterations++;
	}
	free_and_backup_thread(th);
	return (NULL);
}

static void	init_render(t_scene *sc)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		sc->threads[i].id = i;
		sc->threads[i].scene = sc;
		set_thread(&sc->threads[i], &sc->threads_backup[i], sc->do_backup);
		if (pthread_create(&sc->threads[i].self, NULL,
				&set_rendering, (void *)&sc->threads[i]))
		{
			exit (201);
		}
		i++;
	}
	if (sc->do_backup)
	{
		sc->do_backup = false;
		ft_memset(sc->threads_backup, 0, sizeof(t_thread_backup) * THREADS);
	}
}

void	main_loop(void *sc)
{
	t_scene		*scene;

	scene = sc;
	if (!scene->choose_file)
		return ;
	scene->time = mlx_get_time();
	init_render(scene);
}

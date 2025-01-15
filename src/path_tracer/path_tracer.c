/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:44:57 by vpf               #+#    #+#             */
/*   Updated: 2025/01/15 20:36:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "src/path_tracer/scene/scene.h"
#include "src/path_tracer/modes/edit_mode/edit_mode.h"
#include "src/path_tracer/modes/render_mode/render_mode.h"
#include "src/path_tracer/thread_management/thread_management.h"
#include <stdio.h>
#include <stdlib.h>

static void	*set_rendering(void *args)
{
	t_thread 	*thread;

	thread = args;
	while (get_stop_status(thread->scene) == false)
	{
		if (thread->current_y >= thread->y_end)
			thread->current_y = thread->y_start;
		while (get_stop_status(thread->scene) == false && thread->current_y < thread->y_end)
		{
			thread->current_x = thread->x_start;
			while (thread->current_x < thread->x_end)
			{
				if (thread->scene->edit_mode == true)
					edit_mode(thread, thread->current_x, thread->current_y);
				else
					render_mode(thread, thread->current_x, thread->current_y);
				thread->pix_rendered++;
				thread->current_x += thread->x_increment;
			}
			thread->current_y++;
		}
		fprintf(stderr, "THREAD: %i || LAP: %i\r", thread->id, thread->iterations);
		thread->iterations++;
	}
	free(thread->state);
	//printf("THREAD: %i --- || %i || TIME: %f || TIME_HIT: %f\n", thread->id, thread->pix_rendered, mlx_get_time(), thread->time_hit);
	if (get_stop_status(thread->scene)== true)
	{
		thread->scene->threads_backup[thread->id].iterations = thread->iterations - 1;
		thread->scene->threads_backup[thread->id].current_y = thread->current_y;
	}
	return (NULL);
}

static void	init_render(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		scene->threads[i].id = i;
		scene->threads[i].scene = scene;
		set_thread(&scene->threads[i], &scene->threads_backup[i], scene->do_backup);
		if (pthread_create(&scene->threads[i].self, NULL, &set_rendering, (void *)&scene->threads[i]))
			exit (201);
		i++;
	}
	if (scene->do_backup)
	{
		scene->do_backup = false;
		ft_memset(scene->threads_backup, 0, sizeof(t_thread_backup) * THREADS);
	}
}

void	main_loop(void *sc)
{
	t_scene		*scene;

	scene = sc;
	if (!scene->choose_file)
		return ;
	if (!scene->do_backup)
	{
		//set_new_image(scene);
		//mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	}
	scene->time = mlx_get_time();
	init_render(scene);
	//printf("TOT PIX %i || %i\n", scene->height * scene->width, scene->height * scene->width / THREADS);
}

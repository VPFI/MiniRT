/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:37:04 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 21:13:55 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include "path_tracer/scene/objects/texture/texture_objects.h"
#include <stdlib.h>

void	free_texture(t_texture **texture)
{
	if (texture)
	{
		if ((*texture) && (*texture)->path)
			free((*texture)->path);
		if ((*texture) && (*texture)->texture)
		{
			mlx_delete_texture((*texture)->texture);
			free((*texture));
		}
	}
}

void	free_objects(t_object **objects)
{
	t_object *temp;

	if (objects)
	{
		while ((*objects))
		{
			if ((*objects)->texture)
			{
				free_texture(&(*objects)->texture);
			}
			temp = (*objects)->next;
			free((*objects));
			(*objects) = temp;
		}
	}
}

void	free_primitive(t_object **object)
{
	if ((*object)->type == BOX)
	{
		free_objects(&(*object)->figure.box.faces);
	}
	if ((*object)->texture)
	{
		free_texture(&(*object)->texture);
	}
	free(*object);
}

void	free_boxes(t_object *objects)
{
	while (objects)
	{
		if (objects->type == BOX)
			free_objects(&objects->figure.box.faces);
		objects = objects->next;
	}
}

void	clean_memory(t_scene *scene)
{
	pthread_mutex_destroy(&scene->stop_mutex);
	if (scene->mlx)
		mlx_terminate(scene->mlx);
	free(scene->cumulative_image);
	free(scene->path);
	free_boxes(scene->objects);
	free_objects(&scene->objects);
	free_objects(&scene->lights);
	free_objects(&scene->sky_sphere);
	free_texture(&scene->menu_tx);
	free_buttons(scene->buttons, scene->map_count);
	return ;
}

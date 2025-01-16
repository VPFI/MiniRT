/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:45:51 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 21:43:49 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/scene/camera/utils/camera_utils.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/hooks/management/add/object_add.h"
#include "path_tracer/scene/objects/hooks/management/copy/object_copy.h"
#include "path_tracer/scene/objects/hooks/management/delete/object_delete.h"
#include "window_management/key_identifiers/key_identifiers.h"

void	deselect_objects(t_object *objects, t_object *lights, bool *object_selected)
{
	while (objects)
	{
		objects->selected = false;
		objects = objects->next;
	}
	while (lights)
	{
		lights->selected = false;
		lights = lights->next;
	}
	*object_selected = false;
}

void	select_object(t_scene *scene, uint32_t x, uint32_t y)
{
	t_ray		ray;
	t_vect		pixel_offset;
	t_hit_info	hit_info;

	ray.origin = scene->camera.origin;
	pixel_offset = set_pixel(scene->camera, x, y);
	ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
	if (ray_hit_plus_lights(scene->objects, scene->lights, ray, &hit_info))
	{
		hit_info.object->selected = true;
		scene->object_selected = true;
	}
}

t_object	*get_selected_object(t_object *objects, t_object *lights)
{
	while (objects)
	{
		if (objects->selected == true)
			return(objects);
		objects = objects->next;	
	}
	while (lights)
	{
		if (lights->selected == true)
			return(lights);
		lights = lights->next;	
	}
	return (NULL);
}

void	manage_world_objects(t_scene *scene, mlx_key_data_t key_data)
{
	t_ray		camera_ray;
	t_vect		offset_origin;

	if (is_num_key_down(key_data))
	{
		camera_ray = new_ray(scene->camera.orientation, scene->camera.origin);
		offset_origin = vect_add(ray_at(camera_ray, scene->camera.focus_dist + 1), get_random_uvect(&scene->state));
		add_world_object(scene, key_data, &offset_origin);
	}
	else if (key_data.key == MLX_KEY_N && scene->object_selected)
	{
		camera_ray = new_ray(scene->camera.orientation, scene->camera.origin);
		offset_origin = vect_add(ray_at(camera_ray, scene->camera.focus_dist + 1), get_random_uvect(&scene->state));
		copy_world_object(scene, key_data, &offset_origin);
	}
	else if (key_data.key == MLX_KEY_BACKSPACE && scene->object_selected)
	{
		delete_world_object(scene);
	}
}

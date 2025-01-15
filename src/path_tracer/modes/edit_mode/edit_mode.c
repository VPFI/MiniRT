/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:00 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 20:58:55 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/mlx/mlx_utils.h"
#include "src/path_tracer/path_tracer.h"
#include "src/path_tracer/scene/scene.h"
#include "src/path_tracer/scene/ray/ray.h"
#include "src/path_tracer/scene/objects/objects.h"
#include "src/path_tracer/scene/camera/utils/camera_utils.h"
#include "src/path_tracer/utils/color/color_utils.h"
#include "src/path_tracer/thread_management/thread_management.h"
#include "src/path_tracer/scene/background_color/background_color.h"
#include "src/path_tracer/scene/objects/hooks/management/object_management.h"
#include "src/window_management/window_management.h"
#include "src/window_management/key_identifiers/key_identifiers.h"
#include <math.h>

void	edit_mode_hooks(t_scene *scene, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_R && is_press_and_ctrl(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene->threads);
		scene->stop = false;
		scene->edit_mode = false;
		deselect_objects(scene->objects, scene->lights, &scene->object_selected);
		main_loop(scene);
	}
	else if (is_num_key_down(key_data) || is_copy_delete_key_down(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene->threads);
		scene->stop = false;
		manage_world_objects(scene, key_data);
		main_loop(scene);
	}
	else if (is_camera_key_down(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene->threads);
		scene->stop = false;
		if (scene->object_selected)
			transform_object(scene->objects, scene->lights, scene, key_data);
		else
		{
			move_camera(&scene->camera, &scene->back_up_camera, scene->sky_sphere, key_data);
			recalculate_view(&scene->camera, scene->width, scene->height);
		}
		main_loop(scene);
	}
	else if (is_scene_settings_key_down(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene->threads);
		scene->stop = false;
		change_scene_settings(scene, key_data);
		main_loop(scene);
	}
}

static t_color	calc_pixel_color_normal(t_thread *thread, t_scene *scene, t_ray ray)
{
	t_color		color;
	t_hit_info	hit_info;

	if (ray_hit_plus_lights(scene->objects, scene->lights, ray, &hit_info))
	{
		hit_info.point = ray_at(ray, hit_info.t);
		hit_info.normal = hit_info.object->get_normal(&hit_info, &hit_info.object->figure);
		if (hit_info.object->type == LIGHT)
			color = hit_info.object->material.color;
		else
			color = new_color(((hit_info.normal.x + 1) * 0.5), ((hit_info.normal.y + 1) * 0.5), ((hit_info.normal.z + 1) * 0.5));
		if (hit_info.object->selected)
			color = vect_simple_mult(color, 1.5);
		color = vect_simple_div(color, fmaxf((log(hit_info.t) / log(3)), 1.0));
	}
	else
	{
		if (scene->sky_sphere)
			color = get_background_color(thread, &ray);
		else
			color = vect_simple_mult(hexa_to_vect(SILVER), scene->amb_light);
	}
	return (color);
}

void	edit_mode(t_thread *thread, uint32_t x, uint32_t y)
{
	t_ray		ray;
	t_color		color;
	t_vect		pixel_offset;

	ray.origin = defocus_sample(thread->scene->camera, thread->state);
	pixel_offset = set_pixel(thread->scene->camera, x, y);
	ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
	color = calc_pixel_color_normal(thread, thread->scene, ray);
	color = clamp_vect(color, 0.0, 1.0);
	safe_pixel_put(thread->scene, x, y, color);
}

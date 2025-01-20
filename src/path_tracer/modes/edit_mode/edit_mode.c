/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:00 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 15:29:08 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx_utils.h"
#include "path_tracer/path_tracer.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/hooks\
/transformations/object_transformations.h"
#include "path_tracer/scene/camera/utils/camera_utils.h"
#include "path_tracer/utils/color/color_utils.h"
#include "path_tracer/thread_management/thread_management.h"
#include "path_tracer/scene/background_color/background_color.h"
#include "path_tracer/scene/objects/hooks/management/object_management.h"
#include "window_management/window_management.h"
#include "window_management/key_identifiers/key_identifiers.h"
#include <math.h>

static void	manage_movement(t_scene *sc, mlx_key_data_t key)
{
	if (sc->object_selected)
		transform_object(sc->objects, sc->lights, sc, key);
	else
	{
		move_camera(&sc->camera, &sc->back_up_camera, sc->sky_sphere, key);
		recalculate_view(&sc->camera, sc->width, sc->height);
	}
}

void	edit_mode_hooks(t_scene *sc, mlx_key_data_t key)
{
	if (key.key == MLX_KEY_R && is_press_and_ctrl(key))
	{
		stop_and_wait_threads(sc);
		sc->edit_mode = false;
		deselect_objects(sc->objects, sc->lights, &sc->object_selected);
		main_loop(sc);
	}
	else if (is_num_key_down(key) || is_copy_delete_key_down(key))
	{
		stop_and_wait_threads(sc);
		manage_world_objects(sc, key);
		main_loop(sc);
	}
	else if (is_camera_key_down(key))
	{
		stop_and_wait_threads(sc);
		manage_movement(sc, key);
		main_loop(sc);
	}
	else if (is_scene_settings_key_down(key))
	{
		stop_and_wait_threads(sc);
		change_scene_settings(sc, key);
		main_loop(sc);
	}
}

static t_color	calc_pixel_color_normal(t_thread *th, t_scene *scene, t_ray ray)
{
	t_color		color;
	t_hit_info	ht;

	if (ray_hit_plus_lights(scene->objects, scene->lights, ray, &ht))
	{
		ht.point = ray_at(ray, ht.t);
		ht.normal = ht.object->get_normal(&ht, &ht.object->figure);
		if (ht.object->type == LIGHT)
			color = ht.object->material.color;
		else
			color = new_color(((ht.normal.x + 1) * 0.5),
					((ht.normal.y + 1) * 0.5), ((ht.normal.z + 1) * 0.5));
		if (ht.object->selected)
			color = vect_simple_mult(color, 1.5);
		color = vect_simple_div(color, fmaxf((log(ht.t) / log(3)), 1.0));
	}
	else
	{
		if (scene->sky_sphere)
			color = get_background_color(th, &ray);
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

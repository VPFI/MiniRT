/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:51:33 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 15:26:15 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/camera/hooks/camera_hooks.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/math/math_utils.h"
#include "path_tracer/scene/objects/objects.h"
#include "window_management/key_identifiers/key_identifiers.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"

void	move_camera(t_camera *camera, t_camera *backup,
	t_object *skysphere, mlx_key_data_t key_data)
{
	if (is_reset_key_down(key_data))
		check_reset(camera, backup, key_data);
	else if (is_rotation_key_down(key_data))
		check_rotations(camera, key_data);
	else if (is_movement_key_down(key_data))
		check_translations(camera, skysphere, key_data);
	else if (is_settings_key_down(key_data))
		check_settings(camera, key_data);
	return ;
}

static t_vect	get_random_disk_sample(uint32_t *state)
{
	t_vect	res;

	while (true)
	{
		res = new_vect(
			(fast_rand(state) * 2.0) - 1.0,
			(fast_rand(state) * 2.0) - 1.0,
			0.0);
		if (vect_length(res) < 1.0)
			return (res);
	}
}

t_vect	defocus_sample(t_camera camera, uint32_t *state)
{
	t_vect	disk_sample;
	t_vect	res;

	if (camera.defocus_angle <= 0)
		return (camera.origin);
	disk_sample = get_random_disk_sample(state);
	res = vect_add(vect_simple_mult(camera.defocus_disk_u, disk_sample.x),
			vect_simple_mult(camera.defocus_disk_v, disk_sample.y));
	return (vect_add(camera.origin, res));
}

t_vect	set_pixel(t_camera camera, uint32_t x, uint32_t y)
{
	t_vect	res;
	t_vect	aux1;
	t_vect	aux2;

	aux1 = vect_simple_mult(camera.pixel_delta_h, x);
	aux2 = vect_simple_mult(camera.pixel_delta_v, y);
	res = vect_add(aux1, aux2);
	res = vect_add(res, camera.viewport_pixel0);
	return (res);
}

t_vect	set_pixel_offset(t_camera cam, uint32_t x, uint32_t y, uint32_t *state)
{
	t_vect	res;
	t_vect	aux1;
	t_vect	aux2;

	aux1 = vect_simple_mult(cam.pixel_delta_h, (x + (fast_rand(state) - 0.5)));
	aux2 = vect_simple_mult(cam.pixel_delta_v, (y + (fast_rand(state) - 0.5)));
	res = vect_add(aux1, aux2);
	res = vect_add(res, cam.viewport_pixel0);
	return (res);
}

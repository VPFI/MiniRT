/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:29:45 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 19:34:42 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/camera/hooks/settings/camera_settings.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/utils/print/print_utils.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/hooks\
/transformations/object_transformations.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"
#include <stdio.h>

static t_vect	align_camera_to_axis(mlx_key_data_t key_data)
{
	t_vect	res;

	res = new_vect(0.0, 0.0, -1.0);
	if (key_data.key == MLX_KEY_W)
		res = new_vect(0.0, 1.0, 0.0);
	else if (key_data.key == MLX_KEY_A)
		res = new_vect(-1.0, 0.0, 0.0);
	else if (key_data.key == MLX_KEY_S)
		res = new_vect(0.0, -1.0, 0.0);
	else if (key_data.key == MLX_KEY_D)
		res = new_vect(1.0, 0.0, 0.0);
	else if (key_data.key == MLX_KEY_Q)
		res = new_vect(0.0, 0.0, 1.0);
	else if (key_data.key == MLX_KEY_E)
		res = new_vect(0.0, 0.0, -1.0);
	return (res);
}

int	check_rotations(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.modifier == MLX_CONTROL)
	{
		camera->orientation = align_camera_to_axis(key_data);
	}
	else if (key_data.key == MLX_KEY_W)
	{
		rotate_vector(&camera->orientation, camera->u, 0.05);
	}
	else if (key_data.key == MLX_KEY_A)
	{
		rotate_vector(&camera->orientation, camera->v, 0.05);
	}
	else if (key_data.key == MLX_KEY_S)
	{
		rotate_vector(&camera->orientation, camera->u, -0.05);
	}
	else if (key_data.key == MLX_KEY_D)
	{
		rotate_vector(&camera->orientation, camera->v, -0.05);
	}
	print_vec_s(unit_vect(camera->orientation), "New camera orientation");
	return (1);
}

int	check_translations(t_camera *camera, t_object *sky, mlx_key_data_t key_data)
{
	t_vect	change;

	if (key_data.modifier == MLX_CONTROL)
		change = absolute_translate(key_data);
	else
		change = relative_translate(camera, key_data);
	if (sky)
		sky->figure.sphere.center = vect_add(sky->figure.sphere.center, change);
	camera->origin = vect_add(camera->origin, change);
	print_vec_s(camera->origin, "New camera origin: ");
	return (1);
}

int	check_settings(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_F)
	{
		modify_fov(camera, key_data);
		return (1);
	}
	else if (key_data.key == MLX_KEY_G)
	{
		modify_defocus(camera, key_data);
		return (1);
	}
	else if (key_data.key == MLX_KEY_V)
	{
		modify_focus_dist(camera, key_data);
		return (1);
	}
	return (0);
}

int	check_reset(t_camera *camera, t_camera *backup, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_O)
	{
		camera->origin = new_vect(0.0, 0.5, 1.0);
		camera->orientation = new_vect(0.0, 0.0, -1.0);
		return (1);
	}
	else if (key_data.key == MLX_KEY_T)
	{
		*camera = *backup;
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:29:45 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/utils/print/print_utils.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/hooks/transformations/object_transformations.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"
#include <stdio.h>

static t_vect	align_camera_to_axis(mlx_key_data_t key_data)
{
	t_vect	res;

	res = new_vect(0.0, 0.0, -1.0);
	if (key_data.key == MLX_KEY_W)
	{
		res = new_vect(0.0, 1.0, 0.0);
	}
	else if (key_data.key == MLX_KEY_A)
	{
		res = new_vect(-1.0, 0.0, 0.0);
	}
	else if (key_data.key == MLX_KEY_S)
	{
		res = new_vect(0.0, -1.0, 0.0);
	}
	else if (key_data.key == MLX_KEY_D)
	{
		res = new_vect(1.0, 0.0, 0.0);
	}
	else if (key_data.key == MLX_KEY_Q)
	{
		res = new_vect(0.0, 0.0, 1.0);
	}
	else if (key_data.key == MLX_KEY_E)
	{
		res = new_vect(0.0, 0.0, -1.0);
	}
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

int	check_translations(t_camera *camera, t_object *skysphere, mlx_key_data_t key_data)
{
	t_vect	transformation;

	if (key_data.modifier == MLX_CONTROL)
		transformation = absolute_translate(key_data);
	else
		transformation = relative_translate(camera, key_data);
	if (skysphere)
		skysphere->figure.sphere.center = vect_add(skysphere->figure.sphere.center, transformation);
	camera->origin = vect_add(camera->origin, transformation);
	print_vec_s(camera->origin, "New camera origin: ");
	return (1);
}

int	check_settings(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_F)
	{
		if (key_data.modifier == MLX_CONTROL)
		{
			if (camera->fov > 1)
				camera->fov -= 1;
		}
		else
			camera->fov += 1;
		printf("FOV: %f\n", camera->fov);
		return (1);
	}
	else if (key_data.key == MLX_KEY_G)
	{
		if (key_data.modifier == MLX_CONTROL)
		{
			camera->defocus_angle -= 0.25;
			if (camera->defocus_angle < 0)
				camera->defocus_angle = 0;
		}
		else
			camera->defocus_angle += 0.25;
		printf("DEFOCUS ANGLE: %f\n", camera->defocus_angle);
		return (1);
	}
	else if (key_data.key == MLX_KEY_V)
	{
		if (key_data.modifier == MLX_CONTROL)
		{
			if (camera->focus_dist > 1)
				camera->focus_dist -= 0.5;
		}
		else
			camera->focus_dist += 0.5;
		printf("FOCUS DIST: %f\n", camera->focus_dist);
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

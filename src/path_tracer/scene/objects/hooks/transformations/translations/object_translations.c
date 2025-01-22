/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_translations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:41:46 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 19:05:50 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/hooks/transformations\
/object_transformations.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"

t_vect	relative_translate(t_camera *camera, mlx_key_data_t key_data)
{
	t_vect	transformation;

	transformation = new_vect(0.0, 0.0, 0.0);
	if (key_data.key == MLX_KEY_UP)
		transformation = vect_simple_mult(camera->orientation, 0.1);
	else if (key_data.key == MLX_KEY_DOWN)
		transformation = vect_simple_mult(camera->orientation, -0.1);
	else if (key_data.key == MLX_KEY_RIGHT)
		transformation = vect_simple_mult(camera->u, 0.1);
	else if (key_data.key == MLX_KEY_LEFT)
		transformation = vect_simple_mult(camera->u, -0.1);
	else if (key_data.key == MLX_KEY_LEFT_SHIFT)
		transformation = vect_simple_mult(camera->v, -0.1);
	else if (key_data.key == MLX_KEY_SPACE)
		transformation = vect_simple_mult(camera->v, 0.1);
	return (transformation);
}

t_vect	absolute_translate(mlx_key_data_t key_data)
{
	t_vect	transformation;

	transformation = new_vect(0.0, 0.0, 0.0);
	if (key_data.key == MLX_KEY_UP)
		transformation = new_vect(0.0, 0.0, 0.1);
	else if (key_data.key == MLX_KEY_DOWN)
		transformation = new_vect(0.0, 0.0, -0.1);
	else if (key_data.key == MLX_KEY_RIGHT)
		transformation = new_vect(0.1, 0.0, 0.0);
	else if (key_data.key == MLX_KEY_LEFT)
		transformation = new_vect(-0.1, 0.0, 0.0);
	else if (key_data.key == MLX_KEY_LEFT_SHIFT)
		transformation = new_vect(0.0, -0.1, 0.0);
	else if (key_data.key == MLX_KEY_SPACE)
		transformation = new_vect(0.0, 0.1, 0.0);
	return (transformation);
}

void	check_object_translations(t_object *target_object,
	t_camera *camera, mlx_key_data_t key_data)
{
	t_vect	transformation;

	if (key_data.key == MLX_KEY_ENTER)
		transformation = clamp_object_coords(target_object);
	else if (key_data.modifier == MLX_CONTROL)
		transformation = absolute_translate(key_data);
	else
		transformation = relative_translate(camera, key_data);
	if (!zero_vect(transformation))
	{
		target_object->edit_origin(target_object, transformation);
	}
}

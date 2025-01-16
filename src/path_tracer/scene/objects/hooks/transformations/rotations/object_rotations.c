/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:39:28 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 21:40:54 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"
#include <math.h>

int	check_object_rotations(t_object *target_object, t_camera *camera, mlx_key_data_t key_data)
{
	t_vect	transformation;

	transformation = new_vect(0.0, 0.0, 0.0);
	if (key_data.key == MLX_KEY_W)
	{
		transformation.x -= 0.0873;
	}
	else if (key_data.key == MLX_KEY_A)
	{
		transformation.y -= 0.0873;
	}
	else if (key_data.key == MLX_KEY_S)
	{
		transformation.x += 0.0873;
	}
	else if (key_data.key == MLX_KEY_D)
	{
		transformation.y += 0.0873;
	}
	else if (key_data.key == MLX_KEY_Q)
	{
		transformation.z -= 0.0873;
	}
	else if (key_data.key == MLX_KEY_E)
	{
		transformation.z += 0.0873;
	}
	if (!zero_vect(transformation))
	{
		if (key_data.modifier == MLX_CONTROL)
		{
			transformation = vect_simple_mult(transformation, 1 / 0.0873 * M_PI / 2);
		}
		target_object->edit_orientation(target_object, camera, transformation);
		return (1);
	}
	return (0);
}
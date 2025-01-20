/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:42:22 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 18:09:14 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"

static int	subdimension_resize(t_object *object, mlx_key_data_t key_data)
{
	t_vect	transformation;

	if (key_data.key == MLX_KEY_P)
	{
		transformation = new_vect(1.15, 1.0, 1.0);
		if (key_data.modifier == MLX_CONTROL)
			transformation.x = 0.85;
	}
	else if (key_data.key == MLX_KEY_LEFT_BRACKET)
	{
		transformation = new_vect(1.0, 1.15, 1.0);
		if (key_data.modifier == MLX_CONTROL)
			transformation.y = 0.85;
	}
	else if (key_data.key == MLX_KEY_RIGHT_BRACKET)
	{
		transformation = new_vect(1.0, 1.0, 1.15);
		if (key_data.modifier == MLX_CONTROL)
			transformation.z = 0.85;
	}
	else
		return (0);
	object->edit_dimensions(object, transformation);
	return (1);
}

static int	general_resize(t_object *object, mlx_key_data_t key_data)
{
	t_vect	transformation;

	if (key_data.key == MLX_KEY_EQUAL)
	{
		transformation = new_vect(1.15, 1.15, 1.15);
	}
	else if (key_data.key == MLX_KEY_MINUS)
	{
		transformation = new_vect(0.85, 0.85, 0.85);
	}
	else
		return (0);
	object->edit_dimensions(object, transformation);
	return (1);
}

int	check_object_resize(t_object *target_object, mlx_key_data_t key_data)
{
	if (general_resize(target_object, key_data))
		return (1);
	else if (subdimension_resize(target_object, key_data))
		return (1);
	return (0);
}

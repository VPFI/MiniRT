/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:32:51 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/hooks/management/object_management.h"
#include "path_tracer/scene/objects/hooks/transformations/object_transformations.h"
#include "window_management/key_identifiers/key_identifiers.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"
#include <math.h>

t_vect	clamp_object_coords(t_object *target_object)
{
	t_vect	transformation;
	t_vect	obj_origin;

	transformation = new_vect(0.0, 0.0, 0.0);
	obj_origin = target_object->get_origin(target_object);
	transformation.x = roundf(obj_origin.x);
	transformation.y = roundf(obj_origin.y);
	transformation.z = roundf(obj_origin.z);
	transformation = vect_subtract(transformation, obj_origin);
	return (transformation);
}

int	check_object_focus(t_object *target_object, t_scene *scene, mlx_key_data_t key_data)
{
	t_vect	obj_origin;

	if (key_data.key == MLX_KEY_B)
	{
		obj_origin = target_object->get_origin(target_object);
		scene->camera.orientation = unit_vect(vect_subtract(obj_origin, scene->camera.origin));
		recalculate_view(&scene->camera, scene->width, scene->height);
		return (1);
	}
	return (0);
}

void	transform_object(t_object *objects, t_object *lights, t_scene *scene, mlx_key_data_t key_data)
{
	t_object	*target_object;

	target_object = get_selected_object(objects, lights);
	if (!target_object)
		return ;
	if (is_movement_key_down(key_data) || key_data.key == MLX_KEY_ENTER)
		check_object_translations(target_object, &scene->camera, key_data);
	else if (is_rotation_key_down(key_data) || key_data.key == MLX_KEY_ENTER)
		check_object_rotations(target_object, &scene->camera, key_data);
	else if (is_aspect_key_down(key_data))
		check_object_aspect(target_object, key_data);
	else if (check_object_focus(target_object, scene, key_data))
		return ;
	else if (check_object_resize(target_object, key_data))
		return ;
	return ;
}

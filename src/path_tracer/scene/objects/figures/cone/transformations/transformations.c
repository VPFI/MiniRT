/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 21:48:22 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/print/print_utils.h"
#include "path_tracer/utils/rotations/rotations.h"
#include <stdio.h>

void	resize_cone(t_object *object, t_vect transformation)
{
	object->figure.cone.radius *= transformation.x;
	object->figure.cone.height *= transformation.y;
	printf("New Cone radius: %f\n", object->figure.cone.radius);
	printf("New Cone height: %f\n\n", object->figure.cone.height);
	return ;
}

void	rotate_cone(t_object *object, t_camera *camera, t_vect transformation)
{
	(void)camera;
	t_ray	cone_ray;

	cone_ray = new_ray(object->figure.cone.normal, object->figure.cone.center);
	object->figure.cone.center = ray_at(cone_ray, (object->figure.cone.height / 2));
	if (transformation.x)
	{
		rotate_vector(&object->figure.cone.normal, camera->u, transformation.x);
	}
	else if (transformation.y)
	{
		rotate_vector(&object->figure.cone.normal, camera->v, transformation.y);
	}
	else if (transformation.z)
	{
		rotate_vector(&object->figure.cone.normal, camera->orientation, transformation.z);
	}
	cone_ray = new_ray(object->figure.cone.normal, object->figure.cone.center);
	object->figure.cone.center = ray_at(cone_ray, -(object->figure.cone.height / 2));
	object->figure.cone.normal = unit_vect(object->figure.cone.normal);
	print_vec_s(object->figure.cone.normal, "New Cone orientation: ");
	return ;
}

void	translate_cone(t_object *object, t_vect transformation)
{
	object->figure.cone.center = vect_add(object->figure.cone.center, transformation);
	print_vec_s(object->figure.cone.center, "New Cone center: ");
	return ;
}
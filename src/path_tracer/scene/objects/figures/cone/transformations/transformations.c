/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:03:10 by vperez-f         ###   ########.fr       */
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

void	rotate_cone(t_object *obj, t_camera *cam, t_vect transf)
{
	t_ray	cone_ray;

	cone_ray = new_ray(obj->figure.cone.normal, obj->figure.cone.center);
	obj->figure.cone.center = ray_at(cone_ray, (obj->figure.cone.height / 2));
	if (transf.x)
	{
		rotate_vector(&obj->figure.cone.normal, cam->u, transf.x);
	}
	else if (transf.y)
	{
		rotate_vector(&obj->figure.cone.normal, cam->v, transf.y);
	}
	else if (transf.z)
	{
		rotate_vector(&obj->figure.cone.normal, cam->orientation, transf.z);
	}
	cone_ray = new_ray(obj->figure.cone.normal, obj->figure.cone.center);
	obj->figure.cone.center = ray_at(cone_ray, -(obj->figure.cone.height / 2));
	obj->figure.cone.normal = unit_vect(obj->figure.cone.normal);
	print_vec_s(obj->figure.cone.normal, "New Cone orientation: ");
	return ;
}

void	translate_cone(t_object *object, t_vect transf)
{
	object->figure.cone.center = vect_add(object->figure.cone.center, transf);
	print_vec_s(object->figure.cone.center, "New Cone center: ");
	return ;
}

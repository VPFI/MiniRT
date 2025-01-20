/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:29:03 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/print/print_utils.h"
#include "path_tracer/utils/rotations/rotations.h"
#include <stdio.h>

void	resize_cylinder(t_object *object, t_vect transformation)
{
	object->figure.cylinder.radius *= transformation.x;
	object->figure.cylinder.height *= transformation.y;
	printf("New Cylinder radius: %f\n", object->figure.cylinder.radius);
	printf("New Cylinder height: %f\n\n", object->figure.cylinder.height);
	return ;
}

void	rotate_cylinder(t_object *obj, t_camera *cam, t_vect transf)
{
	if (transf.x)
		rotate_vector(&obj->figure.cylinder.normal, cam->u, transf.x);
	else if (transf.y)
		rotate_vector(&obj->figure.cylinder.normal, cam->v, transf.y);
	else if (transf.z)
		rotate_vector(&obj->figure.cylinder.normal, cam->orientation, transf.z);
	obj->figure.cylinder.normal = unit_vect(obj->figure.cylinder.normal);
	print_vec_s(obj->figure.cylinder.normal, "New Cylinder orientation: ");
	return ;
}

void	translate_cylinder(t_object *obj, t_vect transf)
{
	obj->figure.cylinder.center = vect_add(obj->figure.cylinder.center, transf);
	print_vec_s(obj->figure.cylinder.center, "New Cylinder center: ");
	return ;
}

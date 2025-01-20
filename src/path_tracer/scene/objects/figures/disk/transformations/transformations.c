/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:44:54 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/print/print_utils.h"
#include "path_tracer/utils/rotations/rotations.h"
#include <stdio.h>

void	resize_disk(t_object *object, t_vect transformation)
{
	object->figure.disk.radius *= transformation.x;
	printf("New Disk radius: %f\n\n", object->figure.disk.radius);
	return ;
}

void	rotate_disk(t_object *object, t_camera *cam, t_vect transf)
{
	if (transf.x)
		rotate_vector(&object->figure.disk.normal, cam->u, transf.x);
	else if (transf.y)
		rotate_vector(&object->figure.disk.normal, cam->v, transf.y);
	else if (transf.z)
		rotate_vector(&object->figure.disk.normal, cam->orientation, transf.z);
	object->figure.disk.normal = unit_vect(object->figure.disk.normal);
	print_vec_s(object->figure.disk.normal, "New Disk orientation: ");
	return ;
}

void	translate_disk(t_object *obj, t_vect transf)
{
	obj->figure.disk.center = vect_add(obj->figure.disk.center, transf);
	print_vec_s(obj->figure.disk.center, "New Disk center: ");
	return ;
}

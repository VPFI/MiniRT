/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:20:55 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/print/print_utils.h"
#include "path_tracer/utils/rotations/rotations.h"

void	resize_plane(t_object *object, t_vect transformation)
{
	(void)object;
	(void)transformation;
	return ;
}

void	rotate_plane(t_object *object, t_camera *cam, t_vect transf)
{
	if (transf.x)
		rotate_vector(&object->figure.plane.normal, cam->u, transf.x);
	else if (transf.y)
		rotate_vector(&object->figure.plane.normal, cam->v, transf.y);
	else if (transf.z)
		rotate_vector(&object->figure.plane.normal, cam->orientation, transf.z);
	object->figure.plane.normal = unit_vect(object->figure.plane.normal);
	print_vec_s(object->figure.plane.normal, "New Plane orientation: ");
	return ;
}

void	translate_plane(t_object *object, t_vect transf)
{
	object->figure.plane.center = vect_add(object->figure.plane.center, transf);
	print_vec_s(object->figure.plane.center, "New Plane center: ");
	return ;
}

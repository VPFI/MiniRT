/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:06:53 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/print/print_utils.h"
#include <stdio.h>

void	resize_sphere(t_object *object, t_vect transformation)
{
	object->figure.sphere.radius *= transformation.x;
	printf("New sphere radius: %f\n", object->figure.sphere.radius);
	return ;
}

void	rotate_sphere(t_object *object, t_camera *camera, t_vect transformation)
{
	(void)object;
	(void)transformation;
	(void)camera;
	return ;
}

void	translate_sphere(t_object *obj, t_vect transform)
{
	obj->figure.sphere.center = vect_add(obj->figure.sphere.center, transform);
	print_vec_s(obj->figure.sphere.center, "New Sphere center: ");
	return ;
}

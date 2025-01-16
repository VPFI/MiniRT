/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 16:53:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/utils/vectors/vectors.h"
#include "src/path_tracer/scene/objects/objects.h"
#include "src/path_tracer/utils/print/print_utils.h"

void	rotate_point_light(t_object *object, t_camera *camera, t_vect transformation)
{
	(void)object;
	(void)transformation;
	(void)camera;
	return ;
}

void	translate_point_light(t_object *object, t_vect transformation)
{
	object->figure.p_light.location = vect_add(object->figure.p_light.location, transformation);
	print_vec_s(object->figure.p_light.location, "New Point Light center: ");
	return ;
}

void	resize_point_light(t_object *object, t_vect transformation)
{
	object->figure.p_light.radius_shadow *= transformation.x;
	printf("New Point Light radius: %f\n", object->figure.p_light.radius_shadow);
	return ;
}
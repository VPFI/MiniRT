/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:26:14 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/print/print_utils.h"
#include <stdio.h>

void	rotate_point_light(t_object *object, t_camera *camera, t_vect transf)
{
	(void)object;
	(void)transf;
	(void)camera;
	return ;
}

void	translate_point_light(t_object *ob, t_vect transf)
{
	ob->figure.p_light.location = vect_add(ob->figure.p_light.location, transf);
	print_vec_s(ob->figure.p_light.location, "New Point Light center: ");
	return ;
}

void	resize_point_light(t_object *obj, t_vect transformation)
{
	obj->figure.p_light.radius_shadow *= transformation.x;
	printf("New Point Light radius: %f\n", obj->figure.p_light.radius_shadow);
	return ;
}

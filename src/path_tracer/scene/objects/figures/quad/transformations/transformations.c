/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:36:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/print/print_utils.h"
#include "path_tracer/utils/rotations/rotations.h"

void	resize_quad(t_object *ob, t_vect transf)
{
	ob->figure.quad.u_vect = vect_simple_mult(ob->figure.quad.u_vect, transf.x);
	ob->figure.quad.v_vect = vect_simple_mult(ob->figure.quad.v_vect, transf.x);
	return ;
}

void	rotate_quad(t_object *object, t_camera *cam, t_vect transf)
{
	if (transf.x)
	{
		rotate_vector(&object->figure.quad.u_vect, cam->u, transf.x);
		rotate_vector(&object->figure.quad.v_vect, cam->u, transf.x);
	}
	else if (transf.y)
	{
		rotate_vector(&object->figure.quad.u_vect, cam->v, transf.y);
		rotate_vector(&object->figure.quad.v_vect, cam->v, transf.y);
	}
	else if (transf.z)
	{
		rotate_vector(&object->figure.quad.u_vect, cam->orientation, transf.z);
		rotate_vector(&object->figure.quad.v_vect, cam->orientation, transf.z);
	}
	object->figure.quad.normal = unit_vect(
			vect_cross(object->figure.quad.u_vect, object->figure.quad.v_vect));
	print_vec_s(object->figure.quad.normal, "New Quad orientation: ");
	return ;
}

void	translate_quad(t_object *obj, t_vect transf)
{
	obj->figure.quad.center = vect_add(obj->figure.quad.center, transf);
	print_vec_s(obj->figure.quad.center, "New Quad center: ");
	return ;
}

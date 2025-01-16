/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 21:30:53 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/figures/quad/quad.h"
#include "path_tracer/utils/print/print_utils.h"

static void	recalculate_faces(t_object *box, t_vect dimensions)
{
	t_object	*face;
	t_vect		normal;
	t_vect		anti_normal;

	face = box->figure.box.faces;
	normal = unit_vect(vect_cross(box->figure.box.u_vect, box->figure.box.v_vect));
	anti_normal = vect_simple_mult(normal, -1);

	face->figure.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(normal, dimensions.z * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(anti_normal, dimensions.z * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.u_vect, dimensions.x * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.u_vect, -1 * dimensions.x * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, -1 * dimensions.x);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.v_vect, dimensions.y * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y * 0.5));
	face = face->next;
}

void	resize_box(t_object *object, t_vect transformation)
{
	object->figure.box.dimensions = vect_mult(object->figure.box.dimensions, transformation);
	recalculate_faces(object, object->figure.box.dimensions);
	print_vec_s(object->figure.box.dimensions, "New Box dimensions: ");
	return ;
}

void	rotate_box(t_object *object, t_camera *camera, t_vect transformation)
{
	if (transformation.x)
	{
		rotate_vector(&object->figure.box.u_vect, camera->u, transformation.x);
		rotate_vector(&object->figure.box.v_vect, camera->u, transformation.x);
	}
	else if (transformation.y)
	{
		rotate_vector(&object->figure.box.u_vect, camera->v, transformation.y);
		rotate_vector(&object->figure.box.v_vect, camera->v, transformation.y);
	}
	else if (transformation.z)
	{
		rotate_vector(&object->figure.box.u_vect, camera->orientation, transformation.z);
		rotate_vector(&object->figure.box.v_vect, camera->orientation, transformation.z);
	}
	recalculate_faces(object, object->figure.box.dimensions);
	print_vec_s(vect_cross(object->figure.box.u_vect, object->figure.box.v_vect), "New Box orientation: ");
	return ;
}

void	translate_box(t_object *object, t_vect transformation)
{
	t_object	*face;

	face = object->figure.box.faces;
	object->figure.box.center = vect_add(object->figure.box.center, transformation);
	while (face)
	{
		translate_quad(face, transformation);
		face = face->next;
	}
	print_vec_s(object->figure.box.center, "New Box center: ");
	return ;
}

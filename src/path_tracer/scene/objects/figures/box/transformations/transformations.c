/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2025/01/09 17:07:48 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

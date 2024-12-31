/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:29:42 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void	resize_quad(t_object *object, t_vect transformation)
{
	object->figure.quad.u_vect = vect_simple_mult(object->figure.quad.u_vect, transformation.x);
	object->figure.quad.v_vect = vect_simple_mult(object->figure.quad.v_vect, transformation.x);
	return ;
}

void	rotate_quad(t_object *object, t_camera *camera, t_vect transformation)
{
	if (transformation.x)
	{
		rotate_vector(&object->figure.quad.u_vect, camera->u, transformation.x);
		rotate_vector(&object->figure.quad.v_vect, camera->u, transformation.x);
	}
	else if (transformation.y)
	{
		rotate_vector(&object->figure.quad.u_vect, camera->v, transformation.y);
		rotate_vector(&object->figure.quad.v_vect, camera->v, transformation.y);
	}
	else if (transformation.z)
	{
		rotate_vector(&object->figure.quad.u_vect, camera->orientation, transformation.z);
		rotate_vector(&object->figure.quad.v_vect, camera->orientation, transformation.z);
	}
	object->figure.quad.normal = unit_vect(vect_cross(object->figure.quad.u_vect, object->figure.quad.v_vect));
	print_vec_s(object->figure.quad.normal, "New Quad orientation: ");
	return ;
}

void	translate_quad(t_object *object, t_vect transformation)
{
	object->figure.quad.center = vect_add(object->figure.quad.center, transformation);
	print_vec_s(object->figure.quad.center, "New Quad center: ");
	return ;
}
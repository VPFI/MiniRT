/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:24:15 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void	resize_plane(t_object *object, t_vect transformation)
{
	(void)object;
	(void)transformation;
	return ;
}
void	rotate_plane(t_object *object, t_camera *camera, t_vect transformation)
{
	if (transformation.x)
		rotate_vector(&object->figure.plane.normal, camera->u, transformation.x);
	else if (transformation.y)
		rotate_vector(&object->figure.plane.normal, camera->v, transformation.y);
	else if (transformation.z)
		rotate_vector(&object->figure.plane.normal, camera->orientation, transformation.z);
	object->figure.plane.normal = unit_vect(object->figure.plane.normal);
	print_vec_s(object->figure.plane.normal, "New Plane orientation: ");
	return ;
}

void	translate_plane(t_object *object, t_vect transformation)
{
	object->figure.plane.center = vect_add(object->figure.plane.center, transformation);
	print_vec_s(object->figure.plane.center, "New Plane center: ");
	return ;
}
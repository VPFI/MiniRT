/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:39:15 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	resize_cylinder(t_object *object, t_vect transformation)
{
	object->figure.cylinder.radius *= transformation.x;
	object->figure.cylinder.height *= transformation.y;
	printf("New Cylinder radius: %f\n", object->figure.cylinder.radius);
	printf("New Cylinder height: %f\n\n", object->figure.cylinder.height);
	return ;
}

void	rotate_cylinder(t_object *object, t_camera *camera, t_vect transformation)
{
	if (transformation.x)
		rotate_vector(&object->figure.cylinder.normal, camera->u, transformation.x);
	else if (transformation.y)
		rotate_vector(&object->figure.cylinder.normal, camera->v, transformation.y);
	else if (transformation.z)
		rotate_vector(&object->figure.cylinder.normal, camera->orientation, transformation.z);
	object->figure.cylinder.normal = unit_vect(object->figure.cylinder.normal);
	print_vec_s(object->figure.cylinder.normal, "New Cylinder orientation: ");
	return ;
}

void	translate_cylinder(t_object *object, t_vect transformation)
{
	object->figure.cylinder.center = vect_add(object->figure.cylinder.center, transformation);
	print_vec_s(object->figure.cylinder.center, "New Cylinder center: ");
	return ;
}
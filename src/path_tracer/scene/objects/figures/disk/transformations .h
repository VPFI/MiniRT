/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:31:07 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	resize_disk(t_object *object, t_vect transformation)
{
	object->figure.disk.radius *= transformation.x;
	printf("New Disk radius: %f\n\n", object->figure.disk.radius);
	return ;
}

void	rotate_disk(t_object *object, t_camera *camera, t_vect transformation)
{
	if (transformation.x)
		rotate_vector(&object->figure.disk.normal, camera->u, transformation.x);
	else if (transformation.y)
		rotate_vector(&object->figure.disk.normal, camera->v, transformation.y);
	else if (transformation.z)
		rotate_vector(&object->figure.disk.normal, camera->orientation, transformation.z);
	object->figure.disk.normal = unit_vect(object->figure.disk.normal);
	print_vec_s(object->figure.disk.normal, "New Disk orientation: ");
	return ;
}

void	translate_disk(t_object *object, t_vect transformation)
{
	object->figure.disk.center = vect_add(object->figure.disk.center, transformation);
	print_vec_s(object->figure.disk.center, "New Disk center: ");
	return ;
}
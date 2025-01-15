/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:08 by vpf               #+#    #+#             */
/*   Updated: 2024/12/24 23:45:28 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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
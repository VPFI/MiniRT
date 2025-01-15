/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2024/12/24 23:45:55 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



t_vect	get_light_normal(t_hit_info *hit_info, t_figure *fig)
{
	(void)hit_info;
	(void)fig;
	return(new_vect(0.0, 1.0, 0.0));
}

t_vect	get_light_pattern(t_hit_info *hit_info)
{
	return (hit_info->object->material.color);
}

t_vect	get_origin_point_light(t_object *object)
{
	return (object->figure.p_light.location);
}

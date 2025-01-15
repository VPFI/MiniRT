/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:48:26 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:42:31 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



float	get_height(t_vect point, t_vect center, float base)
{
	t_vect		center_to_point;
	float		point_height;
	float		hypotenuse;

	center_to_point = vect_subtract(point, center);
	hypotenuse = vect_dot(center_to_point, center_to_point);
	point_height = sqrt(fabs(hypotenuse - base * base));
	return (point_height);
}

t_vect	compute_cylinder_normal(t_figure *fig, t_hit_info *hit_info, int is_base)
{
	float		point_height;
	t_vect		center_offset;
	t_vect		center_to_point;
	t_vect		normal;

	if (is_base == 1)
		normal = fig->cylinder.normal;
	else if (is_base == -1)
		normal = vect_simple_mult(fig->cylinder.normal, -1.0);
	else
	{
		center_to_point = vect_subtract(hit_info->point, fig->cylinder.center);
		point_height = get_height(hit_info->point, fig->cylinder.center, fig->cylinder.radius);
		if (vect_dot(center_to_point, fig->cylinder.normal) < 0.0)
			point_height *= -1;
		center_offset = vect_add(fig->cylinder.center, vect_simple_mult(fig->cylinder.normal, point_height));
		normal = unit_vect(vect_subtract(hit_info->point, center_offset));
	}
	return (normal);
}
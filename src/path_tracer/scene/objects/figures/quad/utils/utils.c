/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:48:26 by vpf               #+#    #+#             */
/*   Updated: 2025/01/09 17:10:31 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	correct_box_pattern_index(t_vect *dimensions, int face_index, int pattern_index)
{
	if ((face_index == 2 || face_index == 3))
	{
		if (!((int)((dimensions->z - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;
		if (((int)((dimensions->x - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;		
	}
	if ((face_index == 4 || face_index == 5))
	{
		if (((int)((dimensions->z - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;
		if (((int)((dimensions->y - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;
	}
	return (pattern_index);
}

t_vect	get_rotated_point_quad(t_hit_info *hit_info)
{
	t_vect	axis;
	float	angle;
	t_vect	rotated_point;
	t_vect	u_vect_rotated;

	u_vect_rotated = unit_vect(hit_info->object->figure.quad.u_vect);
	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.quad.center);
	rotate_reference_system(hit_info->object->figure.quad.normal, &u_vect_rotated, &rotated_point);
	u_vect_rotated = clamp_vect(u_vect_rotated, -1.0, 1.0);
	axis = new_vect(0.0, 0.0, 1.0);
	angle = acos(-u_vect_rotated.x);
	if (u_vect_rotated.y > 0.0)
		rotate_vector(&rotated_point, axis, angle);
	else if (u_vect_rotated.y < 0.0)
		rotate_vector(&rotated_point, axis, -angle);
	rotated_point.x = round(rotated_point.x * 10000.0) / 10000.0;
	rotated_point.y = round(rotated_point.y * 10000.0) / 10000.0;
	rotated_point.z = round(rotated_point.z * 10000.0) / 10000.0;
	return (rotated_point);
}

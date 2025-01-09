/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:30:14 by vpf              ###   ########.fr       */
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

t_vect	get_quad_texture(t_hit_info *hit_info, t_texture *tx, t_figure *fig)
{
	float	angle;
	float	aux_angle;
	t_vect	texture_normal;
	t_vect	rotated_point;
	t_vect	u_vect_rotated;

	u_vect_rotated = unit_vect(fig->quad.u_vect);
	rotate_reference_system(fig->quad.normal, &u_vect_rotated, NULL);
	u_vect_rotated = clamp_vect(u_vect_rotated, -1.0, 1.0);
	if (u_vect_rotated.y > 0.0)
		aux_angle = acos(-u_vect_rotated.x);
	else if (u_vect_rotated.y < 0.0)
		aux_angle = -acos(-u_vect_rotated.x);
	else
		aux_angle = 0.0;
	rotated_point = get_rotated_point_quad(hit_info);
	angle = rotate_reference_system(fig->quad.normal, NULL, NULL);
	set_bump_map_normal_plane(&rotated_point, tx, &texture_normal);
	rotate_vector(&texture_normal, new_vect(0.0, 0.0, 1.0), -aux_angle);
	rotate_by_angle(&texture_normal, &fig->quad.normal, -angle);
	return (texture_normal);
}

t_vect	get_face_pattern(t_hit_info *hit_info, t_vect *dimensions, int face_index)
{
	t_pattern_vars	p_var;
	t_vect			rotated_point;

	rotated_point = get_rotated_point_quad(hit_info);
	p_var.x_index_square = (int)(fabs(rotated_point.x) / hit_info->object->material.pattern_dim);
	p_var.y_index_square = (int)(fabs(rotated_point.y) / hit_info->object->material.pattern_dim);
	if (rotated_point.x < 0.0)
		p_var.x_index_square++;
	if (rotated_point.y < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	p_var.pattern_index = correct_box_pattern_index(dimensions, face_index, p_var.pattern_index);
	if (p_var.pattern_index == 0)
		return(hit_info->object->material.color);
	else
		return(vect_simple_div(hit_info->object->material.color, 3.0));
}

t_vect	get_quad_pattern(t_hit_info *hit_info)
{
	t_vect	rotated_point;

	rotated_point = get_rotated_point_quad(hit_info);
	return (get_plane_pattern_color(&rotated_point, hit_info->object->material.pattern_dim, &hit_info->object->material.color));
}


t_vect	get_origin_quad(t_object *object)
{
	return (object->figure.quad.center);
}

t_vect	get_quad_normal(t_hit_info *hit_info, t_figure *fig)
{
	if (hit_info->object->texture)
	{
		return (get_quad_texture(hit_info, hit_info->object->texture, fig));
	}
	else
	{
		return (fig->quad.normal);
	}
}

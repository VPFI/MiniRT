/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/09 17:10:28 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

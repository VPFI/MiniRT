/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:31:28 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_vect	get_disk_texture(t_hit_info *hit_info, t_texture *tx, t_figure *fig)
{
	float			angle;
	t_vect			rotated_point;
	t_vect			texture_normal;

	rotated_point = vect_subtract(hit_info->point, fig->disk.center);
	angle = rotate_reference_system(fig->disk.normal, NULL, &rotated_point);
	set_bump_map_normal_disk(fig, &rotated_point, &texture_normal, tx);
	rotate_by_angle(&texture_normal, &fig->disk.normal, -angle);
	return (texture_normal);
}

t_vect	get_base_pattern(t_vect *point, t_figure *figure, float pattern_dim, t_color *obj_color)
{	
	t_pattern_vars	p_var;
	t_base_params	bp;
	float			point_pattern_dim;

	set_base_params(&bp, point, figure->disk.radius);
	point_pattern_dim = bp.point_radius * (pattern_dim / figure->disk.radius);
	p_var.x_index_square = (int)(fabs(bp.point_arc)/ point_pattern_dim);
	p_var.y_index_square = (int)((fabs(bp.base_height) + figure->disk.center.y)  / pattern_dim);
	if (point->x > 0.0)
		p_var.x_index_square++;
	if (point->z > 0.0 && fabs(point->z) > 0.0001)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(*obj_color);
	else
		return(vect_simple_div(*obj_color, 3.0));
}

t_vect	get_disk_pattern(t_hit_info *hit_info)
{	
	t_base_params	bp;
	t_pattern_vars	p_var;
	t_vect			rotated_point;
	float			point_pattern_dim;

	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.disk.center);
	rotate_reference_system(hit_info->object->figure.disk.normal, NULL, &rotated_point);
	set_base_params(&bp, &rotated_point, hit_info->object->figure.disk.radius);
	point_pattern_dim = bp.point_radius * (hit_info->object->material.pattern_dim / hit_info->object->figure.disk.radius);
	p_var.x_index_square = (int)(fabs(bp.point_arc)/ point_pattern_dim);
	p_var.y_index_square = (int)(fabs(bp.base_height) / hit_info->object->material.pattern_dim);
	if (rotated_point.x > 0.0)
		p_var.x_index_square++;
	if (rotated_point.z > 0.0 && fabs(rotated_point.z) > 0.0001)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(hit_info->object->material.color);
	else
		return(vect_simple_div(hit_info->object->material.color, 3.0));
}


t_vect	get_origin_disk(t_object *object)
{
	return (object->figure.disk.center);
}


t_vect	get_disk_normal(t_hit_info *hit_info, t_figure *fig)
{
	if (hit_info->object->texture)
	{
		return (get_disk_texture(hit_info, hit_info->object->texture, fig));
	}
	else
	{
		return (fig->disk.normal);
	}
}

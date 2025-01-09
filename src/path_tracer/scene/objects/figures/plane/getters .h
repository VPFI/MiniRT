/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:25:52 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_vect	get_plane_texture(t_hit_info *hit_info, t_texture *tx, t_figure *fig)
{
	float	angle;
	t_vect	texture_normal;
	t_vect	rotated_point;

	rotated_point = vect_subtract(hit_info->point, fig->plane.center);
	angle = rotate_reference_system(fig->plane.normal, NULL, &rotated_point);
	set_bump_map_normal_plane(&rotated_point, tx, &texture_normal);
	rotate_by_angle(&texture_normal, &fig->plane.normal, -angle);
	return (texture_normal);
}

t_vect	get_plane_pattern_color(t_vect *rotated_point, float pattern_dim, t_vect *material_color)
{
	t_pattern_vars	p_var;

	p_var.x_index_square = (int)(fabs(rotated_point->x) / pattern_dim);
	p_var.y_index_square = (int)(fabs(rotated_point->y) / pattern_dim);
	if (rotated_point->x < 0.0)
		p_var.x_index_square++;
	if (rotated_point->y < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return (*material_color);
	else
		return (vect_simple_div(*material_color, 3.0));	
}

t_vect	get_plane_pattern(t_hit_info *hit_info)
{
	t_vect	rotated_point;

	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.plane.center);
	rotate_reference_system(hit_info->object->figure.plane.normal, NULL, &rotated_point);
	return (get_plane_pattern_color(&rotated_point, hit_info->object->material.pattern_dim, &hit_info->object->material.color));
}

t_vect	get_obj_color(t_hit_info *hit_info)
{
	if (hit_info->object->material.pattern)
		return (hit_info->object->get_visual(hit_info));
	else
		return (hit_info->object->material.color);
}


t_vect	get_origin_plane(t_object *object)
{
	return (object->figure.plane.center);
}


t_vect	get_plane_normal(t_hit_info *hit_info, t_figure *fig)
{
	if (hit_info->object->texture)
	{

		return (get_plane_texture(hit_info, hit_info->object->texture, fig));
	}
	else
	{
		return (fig->plane.normal);
	}
}

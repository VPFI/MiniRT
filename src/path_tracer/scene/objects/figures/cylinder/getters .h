/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:39:56 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_vect	get_cylinder_texture(t_hit_info *ht, t_texture *tx, t_figure *fig, int is_base)
{
	float	angle;
	t_vect	axis;
	t_vect	rotated_point;
	t_vect	reverse_normal;
	t_vect	texture_normal;

	rotated_point = vect_subtract(ht->point, fig->cylinder.center);
	reverse_normal = vect_simple_mult(fig->cylinder.normal, -1.0);
	angle = rotate_reference_system(reverse_normal, NULL, &rotated_point);
	if (is_base)
	{
		set_bump_map_normal_base(&rotated_point, &texture_normal, tx, fig->cylinder.radius, (-fig->cylinder.height / 2) * is_base);
		if (is_base == 1)
		{
			axis = new_vect(0.0, 1.0, 0.0);
			rotate_by_angle(&texture_normal, &axis, M_PI);
		}
	}
	else
		set_bump_map_normal_cylinder(&rotated_point, &texture_normal, tx, fig);
	rotate_by_angle(&texture_normal, &reverse_normal, -angle);
	return (texture_normal);
}

t_vect	get_cylinder_normal(t_hit_info *hit_info, t_figure *fig)
{
	int	is_base;

	is_base = belongs_to_base(hit_info->point, fig->cylinder.center, fig->cylinder.normal, fig->cylinder.height * 0.5);
	if (hit_info->object->texture)
	{
		return (get_cylinder_texture(hit_info, hit_info->object->texture, fig, is_base));
	}
	else
	{
		return (compute_cylinder_normal(fig, hit_info, is_base));
	}
}

t_color	get_cylinder_body_pattern(t_hit_info *hit_info)
{
	t_vect			rotated_point;
	t_pattern_vars	p_var;

	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.cylinder.center);
	rotate_reference_system(hit_info->object->figure.cylinder.normal, NULL, &rotated_point);
	p_var.x_index_square = (int)(fabs(acos(get_vector_arc_height(&rotated_point)) * hit_info->object->figure.cylinder.radius) / hit_info->object->material.pattern_dim);
	p_var.y_index_square = (int)(rotated_point.z / hit_info->object->material.pattern_dim);
	if (rotated_point.x < 0.0)
		p_var.x_index_square++;
	if (rotated_point.z < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(hit_info->object->material.color);
	else
		return(vect_simple_div(hit_info->object->material.color, 3.0));	
}

t_vect	get_cylinder_pattern(t_hit_info *ht)
{
	t_figure	base;
	int			is_base;
	t_vect		rotated_point;

	is_base = belongs_to_base(ht->point, ht->object->figure.cylinder.center, ht->object->figure.cylinder.normal, ht->object->figure.cylinder.height / 2);
	if (is_base)
	{
		base.disk.center.y = ht->object->figure.cylinder.height / 2;
		base.disk.radius = ht->object->figure.cylinder.radius;
		rotated_point = vect_subtract(ht->point, ht->object->figure.cylinder.center);
		rotate_reference_system(ht->object->figure.cylinder.normal, NULL, &rotated_point);
		return (get_base_pattern(&rotated_point, &base, ht->object->material.pattern_dim, &ht->object->material.color));
	}
	else
		return (get_cylinder_body_pattern(ht));
}


t_vect	get_origin_cylinder(t_object *object)
{
	return (object->figure.cylinder.center);
}

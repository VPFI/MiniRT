/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 19:14:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/disk/base/base.h"
#include "path_tracer/scene/objects/figures/cone/textures/texture.h"
#include "path_tracer/scene/objects/figures/cone/utils/utils.h"
#include "path_tracer/utils/rotations/rotations.h"
#include <math.h>

static t_vect	get_cone_body_pattern(t_hit_info *hit_info)
{
	t_vect			rotated_point;
	float			point_radius;
	float			point_pattern_dim;
	t_pattern_vars	p_var;

	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.cone.center);
	rotate_reference_system(hit_info->object->figure.cone.normal, NULL, &rotated_point);
	point_radius = rotated_point.z	* (hit_info->object->figure.cone.radius / hit_info->object->figure.cone.height);
	point_pattern_dim = point_radius * (hit_info->object->material.pattern_dim / hit_info->object->figure.cone.radius);
	p_var.x_index_square = (int)(fabs(acos(get_vector_arc_height(&rotated_point)) * point_radius) / point_pattern_dim);
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

t_vect	get_cone_pattern(t_hit_info *ht)
{
	t_figure	base;
	t_vect		rotated_point;

	if (belongs_to_base(ht->point, ht->object->figure.cone.center, ht->object->figure.cone.normal, ht->object->figure.cone.height))
	{
		base.disk.radius = ht->object->figure.cone.radius;
		base.disk.center.y = ht->object->figure.cone.height;
		base.disk.radius = ht->object->figure.cone.radius;
		rotated_point = vect_subtract(ht->point, ht->object->figure.cone.center);
		rotate_reference_system(ht->object->figure.cone.normal, NULL, &rotated_point);
		return (get_base_pattern(&rotated_point, &base, ht->object->material.pattern_dim, &ht->object->material.color));
	}
	else
		return (get_cone_body_pattern(ht));
}

t_vect	get_origin_cone(t_object *object)
{
	return (object->figure.cone.center);
}

t_vect	get_cone_normal(t_hit_info *hit_info, t_figure *fig)
{
	int	is_base;

	is_base = belongs_to_base(hit_info->point, fig->cone.center, fig->cone.normal, fig->cone.height);
	if (hit_info->object->texture)
	{
		return (get_cone_texture(hit_info, hit_info->object->texture, fig, is_base));
	}
	else
	{
		return (compute_cone_normal(fig, hit_info, is_base));
	}
}

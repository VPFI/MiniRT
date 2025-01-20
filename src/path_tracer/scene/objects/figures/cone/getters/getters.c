/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:10:16 by vperez-f         ###   ########.fr       */
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

static t_vect	get_cone_body_pattern(t_hit_info *ht)
{
	t_vect			rot_pt;
	float			point_radius;
	float			point_pattern_dim;
	t_pattern_vars	p_var;

	rot_pt = vect_subtract(ht->point, ht->object->figure.cone.center);
	rotate_reference_system(ht->object->figure.cone.normal, NULL, &rot_pt);
	point_radius = rot_pt.z
		* (ht->object->figure.cone.radius / ht->object->figure.cone.height);
	point_pattern_dim = point_radius
		* (ht->object->material.pattern_dim / ht->object->figure.cone.radius);
	p_var.x_index_square = (int)(fabs(acos(get_vector_arc_height(&rot_pt))
		* point_radius) / point_pattern_dim);
	p_var.y_index_square = (int)(rot_pt.z / ht->object->material.pattern_dim);
	if (rot_pt.x < 0.0)
		p_var.x_index_square++;
	if (rot_pt.z < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2)
			+ (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(ht->object->material.color);
	else
		return(vect_simple_div(ht->object->material.color, 3.0));
}

t_vect	get_cone_pattern(t_hit_info *ht)
{
	t_figure	base;
	t_vect		rot_pt;

	if (belongs_to_base(ht->point, ht->object->figure.cone.center,
		ht->object->figure.cone.normal, ht->object->figure.cone.height))
	{
		base.disk.radius = ht->object->figure.cone.radius;
		base.disk.center.y = ht->object->figure.cone.height;
		base.disk.radius = ht->object->figure.cone.radius;
		rot_pt = vect_subtract(ht->point, ht->object->figure.cone.center);
		rotate_reference_system(ht->object->figure.cone.normal, NULL, &rot_pt);
		return (get_base_pattern(&rot_pt, &base,
			ht->object->material.pattern_dim, &ht->object->material.color));
	}
	else
		return (get_cone_body_pattern(ht));
}

t_vect	get_origin_cone(t_object *object)
{
	return (object->figure.cone.center);
}

t_vect	get_cone_normal(t_hit_info *ht, t_figure *fig)
{
	int	is_base;

	is_base = belongs_to_base(ht->point, fig->cone.center,
		fig->cone.normal, fig->cone.height);
	if (ht->object->texture)
	{
		return (get_cone_texture(ht, ht->object->texture, fig, is_base));
	}
	else
	{
		return (compute_cone_normal(fig, ht, is_base));
	}
}

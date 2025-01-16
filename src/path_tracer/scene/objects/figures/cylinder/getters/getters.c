/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 16:24:39 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/utils/vectors/vectors.h"
#include "src/path_tracer/utils/rotations/rotations.h"
#include "src/path_tracer/scene/objects/objects.h"
#include "src/path_tracer/scene/objects/figures/shared.h"
#include "src/path_tracer/scene/objects/figures/disk/base/base.h"
#include "src/path_tracer/scene/objects/figures/cylinder/utils/utils.h"
#include "src/path_tracer/scene/objects/figures/cylinder/textures/texture.h"
#include <math.h>

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

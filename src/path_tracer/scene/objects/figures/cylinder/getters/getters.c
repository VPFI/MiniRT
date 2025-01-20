/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:32:03 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/disk/base/base.h"
#include "path_tracer/scene/objects/figures/cylinder/utils/utils.h"
#include "path_tracer/scene/objects/figures/cylinder/textures/texture.h"
#include <math.h>

t_vect	get_cylinder_normal(t_hit_info *ht, t_figure *fig)
{
	int	is_base;

	is_base = belongs_to_base(ht->point, fig->cylinder.center,
			fig->cylinder.normal, fig->cylinder.height * 0.5);
	if (ht->object->texture)
	{
		return (get_cylinder_texture(ht, ht->object->texture, fig, is_base));
	}
	else
	{
		return (compute_cylinder_normal(fig, ht, is_base));
	}
}

t_vect	get_cylinder_pattern(t_hit_info *ht)
{
	t_figure	base;
	int			is_base;
	t_vect		rot_pt;

	is_base = belongs_to_base(ht->point, ht->object->figure.cylinder.center,
			ht->object->figure.cylinder.normal,
			ht->object->figure.cylinder.height / 2);
	if (is_base)
	{
		base.disk.center.y = ht->object->figure.cylinder.height / 2;
		base.disk.radius = ht->object->figure.cylinder.radius;
		rot_pt = vect_subtract(ht->point, ht->object->figure.cylinder.center);
		rotate_reference_system(ht->object->figure.cylinder.normal,
			NULL, &rot_pt);
		return (get_base_pattern(&rot_pt, &base,
				ht->object->material.pattern_dim, &ht->object->material.color));
	}
	else
		return (get_cylinder_body_pattern(ht));
}

t_vect	get_origin_cylinder(t_object *object)
{
	return (object->figure.cylinder.center);
}

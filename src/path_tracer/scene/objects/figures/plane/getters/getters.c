/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:41:41 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/plane/textures/texture.h"
#include <math.h>

static t_vect	get_plane_pattern_color(t_vect *rotated_point,
	float pattern_dim, t_vect *material_color)
{
	t_pattern_vars	p_var;

	p_var.x_index_square = (int)(fabs(rotated_point->x) / pattern_dim);
	p_var.y_index_square = (int)(fabs(rotated_point->y) / pattern_dim);
	if (rotated_point->x < 0.0)
		p_var.x_index_square++;
	if (rotated_point->y < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2)
			+ (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return (*material_color);
	else
		return (vect_simple_div(*material_color, 3.0));
}

t_vect	get_plane_pattern(t_hit_info *ht)
{
	t_vect	rot_p;

	rot_p = vect_subtract(ht->point, ht->object->figure.plane.center);
	rotate_reference_system(ht->object->figure.plane.normal, NULL, &rot_p);
	return (get_plane_pattern_color(&rot_p, ht->object->material.pattern_dim,
			&ht->object->material.color));
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

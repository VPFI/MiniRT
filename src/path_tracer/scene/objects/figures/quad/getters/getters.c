/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:38:18 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/quad/textures/texture.h"
#include <math.h>

static t_vect	get_quad_pattern_color(t_vect *rotated_point,
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

t_vect	get_quad_pattern(t_hit_info *hit_info)
{
	t_vect	rotated_point;

	rotated_point = get_rotated_point_quad(hit_info);
	return (get_quad_pattern_color(&rotated_point,
			hit_info->object->material.pattern_dim,
			&hit_info->object->material.color));
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

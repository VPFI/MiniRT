/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:26:07 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/sphere/utils/utils.h"
#include "path_tracer/scene/objects/figures/sphere/textures/texture.h"
#include <math.h>

t_vect	get_sphere_pattern(t_hit_info *ht)
{
	t_vect			point;
	t_pattern_vars	p_var;
	float			polar[2];
	float			proj_pattern;

	point = vect_subtract(ht->point, ht->object->figure.sphere.center);
	set_polar_coords(&point, &ht->object->figure, polar);
	proj_pattern = sqrtf(pow(point.x, 2) + pow(point.z, 2))
		* ((M_PI / 8) / ht->object->figure.sphere.radius);
	p_var.x_index_square = (int)(fabs(polar[LATITUDE]) / proj_pattern);
	p_var.y_index_square = (int)(fabs(polar[LONGITUDE]) / (M_PI / 8));
	if (point.x < 0.0)
		p_var.x_index_square++;
	if (point.y < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2)
			+ (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return (ht->object->material.color);
	else
		return (vect_simple_div(ht->object->material.color, 3.0));
}

t_vect	get_origin_sphere(t_object *object)
{
	return (object->figure.sphere.center);
}

t_vect	get_sphere_normal(t_hit_info *hit_info, t_figure *fig)
{
	if (hit_info->object->texture)
	{
		return (get_sphere_texture(hit_info, hit_info->object->texture));
	}
	else
	{
		return (vect_simple_div(vect_subtract(hit_info->point,
					fig->sphere.center), fig->sphere.radius));
	}
}

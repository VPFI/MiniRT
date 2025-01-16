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
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/sphere/utils/utils.h"
#include "path_tracer/scene/objects/figures/sphere/textures/texture.h"
#include <math.h>

t_vect	get_sphere_pattern(t_hit_info *hit_info)
{
	t_vect			point;
	t_pattern_vars	p_var;
	float			polar_coords[2];
	float			projected_pattern;

	point = vect_subtract(hit_info->point, hit_info->object->figure.sphere.center);
	set_polar_coords(&point, &hit_info->object->figure, polar_coords);
	projected_pattern = sqrtf(pow(point.x, 2) + pow(point.z, 2)) * ((M_PI / 8) / hit_info->object->figure.sphere.radius); // Pattern-dim / radius
	p_var.x_index_square = (int)(fabs(polar_coords[LATITUDE]) / projected_pattern);
	p_var.y_index_square = (int)(fabs(polar_coords[LONGITUDE]) / (M_PI / 8));
	if (point.x < 0.0)
		p_var.x_index_square++;
	if (point.y < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(hit_info->object->material.color);
	else
		return(vect_simple_div(hit_info->object->material.color, 3.0));
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
		return (vect_simple_div(vect_subtract(hit_info->point, fig->sphere.center), fig->sphere.radius));
	}
}

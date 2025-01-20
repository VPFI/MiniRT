/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:48:26 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:28:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include <math.h>

float	get_height(t_vect point, t_vect center, float base)
{
	t_vect		center_to_point;
	float		point_height;
	float		hypotenuse;

	center_to_point = vect_subtract(point, center);
	hypotenuse = vect_dot(center_to_point, center_to_point);
	point_height = sqrt(fabs(hypotenuse - base * base));
	return (point_height);
}

t_color	get_cylinder_body_pattern(t_hit_info *ht)
{
	t_vect			rot_pt;
	t_pattern_vars	p_var;

	rot_pt = vect_subtract(ht->point, ht->object->figure.cylinder.center);
	rotate_reference_system(ht->object->figure.cylinder.normal, NULL, &rot_pt);
	p_var.x_index_square = (int)(fabs(acos(get_vector_arc_height(&rot_pt))
				* ht->object->figure.cylinder.radius)
			/ ht->object->material.pattern_dim);
	p_var.y_index_square = (int)(rot_pt.z / ht->object->material.pattern_dim);
	if (rot_pt.x < 0.0)
		p_var.x_index_square++;
	if (rot_pt.z < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2)
			+ (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return (ht->object->material.color);
	else
		return (vect_simple_div(ht->object->material.color, 3.0));
}

t_vect	compute_cylinder_normal(t_figure *fig, t_hit_info *ht, int is_base)
{
	float		point_height;
	t_vect		center_offset;
	t_vect		center_to_point;
	t_vect		normal;

	if (is_base == 1)
		normal = fig->cylinder.normal;
	else if (is_base == -1)
		normal = vect_simple_mult(fig->cylinder.normal, -1.0);
	else
	{
		center_to_point = vect_subtract(ht->point, fig->cylinder.center);
		point_height = get_height(ht->point,
				fig->cylinder.center, fig->cylinder.radius);
		if (vect_dot(center_to_point, fig->cylinder.normal) < 0.0)
		{
			point_height *= -1;
		}
		center_offset = vect_add(fig->cylinder.center,
				vect_simple_mult(fig->cylinder.normal, point_height));
		normal = unit_vect(vect_subtract(ht->point, center_offset));
	}
	return (normal);
}

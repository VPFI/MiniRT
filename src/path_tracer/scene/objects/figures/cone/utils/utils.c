/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:48:26 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:00:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include <math.h>

static t_vect	calculate_ideal_normal(t_vect point,
	t_figure fig, float *refsys_angle)
{
	float		angle;
	t_vect		res;
	t_vect		axis;
	t_vect		projected;
	t_vect		center_to_point;

	center_to_point = vect_subtract(point, fig.cone.center);
	*refsys_angle = rotate_reference_system(fig.cone.normal,
			NULL, &center_to_point);
	projected = center_to_point;
	projected.z = 0;
	projected = unit_vect(projected);
	axis = vect_cross(center_to_point, projected);
	axis = unit_vect(axis);
	angle = sin(fig.cone.radius
			/ hypot(fig.cone.radius, fig.cone.height));
	rotate_vector(&projected, axis, angle);
	res = unit_vect(projected);
	return (res);
}

t_vect	compute_cone_normal(t_figure *fig, t_hit_info *hit_info, int is_base)
{
	t_vect		ideal;
	t_vect		axis;
	t_vect		normal;
	float		refsys_angle;

	if (is_base == 1)
		normal = fig->cone.normal;
	else
	{
		normal = calculate_ideal_normal(hit_info->point, *fig, &refsys_angle);
		ideal = new_vect(0.0, 0.0, 1.0);
		if (vect_dot(fig->cone.normal, ideal) == -1.0)
			axis = new_vect(0.0, 1.0, 0.0);
		else
			axis = vect_cross(fig->cone.normal, ideal);
		axis = unit_vect(axis);
		rotate_vector(&normal, axis, -refsys_angle);
	}
	return (normal);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:37:25 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 19:14:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/utils/math/math_utils.h"
#include <math.h>

t_vect	get_rotated_point_quad(t_hit_info *hit_info)
{
	t_vect	axis;
	float	angle;
	t_vect	rotated_point;
	t_vect	u_vect_rotated;

	u_vect_rotated = unit_vect(hit_info->object->figure.quad.u_vect);
	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.quad.center);
	rotate_reference_system(hit_info->object->figure.quad.normal, &u_vect_rotated, &rotated_point);
	u_vect_rotated = clamp_vect(u_vect_rotated, -1.0, 1.0);
	axis = new_vect(0.0, 0.0, 1.0);
	angle = acos(-u_vect_rotated.x);
	if (u_vect_rotated.y > 0.0)
		rotate_vector(&rotated_point, axis, angle);
	else if (u_vect_rotated.y < 0.0)
		rotate_vector(&rotated_point, axis, -angle);
	rotated_point.x = round(rotated_point.x * 10000.0) / 10000.0;
	rotated_point.y = round(rotated_point.y * 10000.0) / 10000.0;
	rotated_point.z = round(rotated_point.z * 10000.0) / 10000.0;
	return (rotated_point);
}

float	get_point_angle(t_vect *point)
{
	float	angle;
	t_vect	center_to_point;

	center_to_point = *point;
	center_to_point.z = 0;
	center_to_point = unit_vect(center_to_point);
	center_to_point.y = f_clamp(center_to_point.y, -1.0, 1.0);
	angle = acosf(center_to_point.y);
	return (angle);
}

float	get_vector_arc_height(t_vect *point)
{
	t_vect	point_arc_vector;

	point_arc_vector = *point;
	point_arc_vector.z = 0.0f;
	point_arc_vector = unit_vect(point_arc_vector);
	return (f_clamp(point_arc_vector.y, -1.0, 1.0));
}

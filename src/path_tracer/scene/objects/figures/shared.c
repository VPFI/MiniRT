/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:37:25 by vpf               #+#    #+#             */
/*   Updated: 2025/01/15 21:40:08 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/utils/vectors/vectors.h"
#include "src/path_tracer/utils/math/math_utils.h"
#include <math.h>

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

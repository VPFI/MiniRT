/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:48:26 by vpf               #+#    #+#             */
/*   Updated: 2025/01/14 22:15:17 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/utils/math/math_utils.h"
#include "src/path_tracer/scene/objects/figures/sphere/utils.h"
#include <math.h>

void	set_polar_coords(t_vect *point, t_figure *fig, float *polar_coords)
{
	float		projected_radius;
	t_vect		point_normal;
	t_vect		latitude_normal;

	point_normal = *point;
	latitude_normal = *point;
	latitude_normal.y = 0.0;
	latitude_normal = unit_vect(latitude_normal);
	point_normal = unit_vect(point_normal);
	projected_radius = sqrtf(pow(point->x, 2) + pow(point->z, 2));
	polar_coords[LATITUDE] = acosf(f_clamp(latitude_normal.z, -1.0, 1.0)) * projected_radius;
	polar_coords[LONGITUDE] = acosf(f_clamp(vect_dot(point_normal, latitude_normal), -1.0, 1.0)) * fig->sphere.radius;
}

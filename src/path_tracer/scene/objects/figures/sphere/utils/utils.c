/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:48:26 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:25:09 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/math/math_utils.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include "path_tracer/scene/objects/figures/sphere/utils/utils.h"
#include <math.h>

void	set_polar_coords(t_vect *point, t_figure *fig, float *polar)
{
	float		projected_radius;
	t_vect		point_normal;
	t_vect		lat_norm;

	point_normal = *point;
	lat_norm = *point;
	lat_norm.y = 0.0;
	lat_norm = unit_vect(lat_norm);
	point_normal = unit_vect(point_normal);
	projected_radius = sqrtf(pow(point->x, 2) + pow(point->z, 2));
	polar[LATITUDE] = acosf(f_clamp(lat_norm.z, -1.0, 1.0)) * projected_radius;
	polar[LONGITUDE] = acosf(f_clamp(vect_dot
				(point_normal, lat_norm), -1.0, 1.0))
		* fig->sphere.radius;
}

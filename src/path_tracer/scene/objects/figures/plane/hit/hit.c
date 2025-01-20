/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:22:19 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include <math.h>

bool	hit_plane(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	float	denominator;
	float	root;
	t_vect	point;

	denominator = vect_dot(fig.plane.normal, ray.dir);
	if (fabs(denominator) < 1e-8)
		return (false);
	point = vect_subtract(ray.origin, fig.plane.center);
	root = -1 * (vect_dot(fig.plane.normal, point)) / denominator;
	if (root <= bounds[MIN] || bounds[MAX] <= root)
	{
		return (false);
	}
	hit_info->t = root;
	return (true);
}

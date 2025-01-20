/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:47:28 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include <math.h>

bool	hit_disk(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	float	denominator;
	float	root;
	float	q;
	t_vect	hit_origin;

	denominator = vect_dot(fig.disk.normal, ray.dir);
	if (fabs(denominator) < 1e-8)
		return (false);
	q = vect_dot(fig.disk.center, fig.disk.normal);
	root = (q - vect_dot(ray.origin, fig.disk.normal)) / denominator;
	if (root <= bounds[MIN] || bounds[MAX] <= root)
	{
		return (false);
	}
	hit_origin = vect_subtract(ray_at(ray, root), fig.disk.center);
	if (vect_length(hit_origin) > (fig.disk.radius))
	{
		return (false);
	}
	hit_info->t = root;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:42:10 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include <math.h>

bool	hit_point_light(t_ray ray, t_figure fig, t_hit_info *ht, float *bounds)
{
	t_eq_params	params;
	t_vect		oc;
	float		sqrt_disc;

	oc = vect_subtract(fig.p_light.location, ray.origin);
	params.a = vect_dot(ray.dir, ray.dir);
	params.b = vect_dot(ray.dir, oc);
	params.c = vect_dot(oc, oc) - (0.2 * 0.2);
	params.discr = (params.b * params.b) - (params.a * params.c);
	if (params.discr < 0)
		return (false);
	sqrt_disc = sqrtf(params.discr);
	params.root = (params.b - sqrt_disc) / params.a;
	if (params.root <= bounds[MIN] || bounds[MAX] <= params.root)
	{
		params.root = (params.b + sqrt_disc) / params.a;
		if (params.root <= bounds[MIN] || bounds[MAX] <= params.root)
			return (false);
	}
	ht->t = params.root;
	ht->point = ray_at(ray, params.root);
	ht->normal = vect_simple_div(
			vect_subtract(ht->point, fig.p_light.location), 0.2);
	return (true);
}

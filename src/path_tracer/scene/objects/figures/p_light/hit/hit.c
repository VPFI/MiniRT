/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 16:49:13 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/scene/ray/ray.h"
#include "src/path_tracer/utils/vectors/vectors.h"
#include "src/path_tracer/scene/objects/objects.h"
#include "src/path_tracer/scene/objects/figures/shared.h"
#include <math.h>

bool	hit_point_light(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
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
	hit_info->t = params.root;
	hit_info->point = ray_at(ray, params.root);
	hit_info->normal = vect_simple_div(vect_subtract(hit_info->point, fig.p_light.location), 0.2);
	return (true);	
}

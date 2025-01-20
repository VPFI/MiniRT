/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:37:42 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include <math.h>

bool	hit_quad(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_eq_params	par;
	t_vect		hit_origin;
	t_vect		n;
	t_vect		w;

	n = vect_cross(fig.quad.u_vect, fig.quad.v_vect);
	w = vect_simple_div(n, vect_dot(n, n));
	par.c = vect_dot(fig.quad.normal, ray.dir);
	if (fabs(par.c) < 1e-8)
		return (false);
	par.root = ((vect_dot(fig.quad.normal, fig.quad.center))
			- vect_dot(ray.origin, fig.quad.normal)) / par.c;
	if (par.root <= bounds[MIN] || bounds[MAX] <= par.root)
	{
		return (false);
	}
	hit_origin = vect_subtract(ray_at(ray, par.root), fig.quad.center);
	par.a = vect_dot(w, vect_cross(hit_origin, fig.quad.v_vect));
	par.b = vect_dot(w, vect_cross(fig.quad.u_vect, hit_origin));
	if ((par.a > 0.5 || par.a < -0.5) || (par.b > 0.5 || par.b < -0.5))
	{
		return (false);
	}
	hit_info->t = par.root;
	return (true);
}

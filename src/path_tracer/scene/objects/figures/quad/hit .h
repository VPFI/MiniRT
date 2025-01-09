/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:28:55 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


bool	hit_quad(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_eq_params	params;
	t_vect		hit_origin;
	t_vect		n;
	t_vect		w;

	n = vect_cross(fig.quad.u_vect, fig.quad.v_vect);
	w = vect_simple_div(n, vect_dot(n, n));
	params.c = vect_dot(fig.quad.normal, ray.dir);
	if (fabs(params.c) < 1e-8)
		return (false);
	params.root = ((vect_dot(fig.quad.normal, fig.quad.center)) - vect_dot(ray.origin, fig.quad.normal)) / params.c;
	if (params.root <= bounds[MIN] || bounds[MAX] <= params.root)
	{
		return (false);
	}
	hit_origin = vect_subtract(ray_at(ray, params.root), fig.quad.center);
	params.a = vect_dot(w, vect_cross(hit_origin, fig.quad.v_vect));
	params.b = vect_dot(w, vect_cross(fig.quad.u_vect, hit_origin));
	if ((params.a > 0.5 || params.a < -0.5) || (params.b > 0.5 || params.b < -0.5))
	{
		return (false);
	}
	hit_info->t = params.root;
	return (true);
}

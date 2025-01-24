/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_scatter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:06:47 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/24 13:58:36 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/material/scatters/scatters.h"
#include "path_tracer/thread_management/thread_management.h"
#include "path_tracer/utils/math/math_utils.h"
#include <stdbool.h>

static int	reflect_check(t_thread *thread, t_hit_info ht, t_ray ray)
{
	float	cos;

	cos = vect_dot(vect_simple_mult(ray.dir, -1.0), ht.normal);
	if (ht.object->material.specular > fast_rand(thread->state)
		|| (reflectance(1.5, cos) > fast_rand(thread->state)
			&& ht.object->material.specular))
	{
		return (1);
	}
	else
		return (0);
}

static void	check_2d(t_hit_info *hit_info, t_ray ray)
{
	if (!hit_info->object->texture && is_2d(hit_info->object))
	{
		check_normal(&hit_info->normal, &ray.dir);
	}
}

static int	check_emissive(t_hit_info *ht, t_color *emittance)
{
	if (ht->object->material.type == EMISSIVE)
	{
		*emittance = vect_simple_mult(get_obj_color(ht),
				ht->object->material.emission_intensity);
		return (1);
	}
	else
		return (0);
}

bool	scatter_ray(t_thread *th, t_hit_info hit_info,
	t_scatter_rays *r, t_color *emittance)
{
	if (check_emissive(&hit_info, emittance))
		return (false);
	check_2d(&hit_info, r->inc_ray);
	if (hit_info.object->material.type == LAMBERTIAN)
		r->out_ray = lambertian_scatter(hit_info, emittance, th);
	else if (hit_info.object->material.type == METAL)
	{
		r->out_ray = metal_scatter(hit_info, r->inc_ray, emittance, th);
		if (vect_dot(r->out_ray.dir, hit_info.normal) <= 0)
			return (false);
	}
	else if (hit_info.object->material.type == DIELECTRIC)
		r->out_ray = dielectric_scatter(hit_info, r->inc_ray, emittance, th);
	else if (hit_info.object->material.type == GLOSSY)
	{
		if (reflect_check(th, hit_info, r->inc_ray))
		{
			r->out_ray = metal_scatter(hit_info, r->inc_ray, emittance, th);
			if (vect_dot(r->out_ray.dir, hit_info.normal) <= 0)
				return (false);
		}
		else
			r->out_ray = lambertian_scatter(hit_info, emittance, th);
	}
	return (true);
}

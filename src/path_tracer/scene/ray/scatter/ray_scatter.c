/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_scatter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:06:47 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 18:57:49 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/material/scatters/scatters.h"
#include "path_tracer/thread_management/thread_management.h"
#include "path_tracer/utils/math/math_utils.h"
#include <stdbool.h>

bool	scatter_ray(t_thread *thread, t_hit_info hit_info, t_ray *bounce_ray, t_ray ray, t_color *emittance)
{
	if (hit_info.object->material.type == EMISSIVE)
	{
		*emittance = vect_simple_mult(get_obj_color(&hit_info), hit_info.object->material.emission_intensity);
		return (false);
	}
	if (!hit_info.object->texture && is_2d(hit_info.object))
	{
		check_normal(&hit_info.normal, &ray.dir);
	}
	if (hit_info.object->material.type == LAMBERTIAN)
	{
		(*bounce_ray) = lambertian_scatter(hit_info, emittance, thread);
	}
	else if (hit_info.object->material.type == METAL)
	{
		(*bounce_ray) = metal_scatter(hit_info, ray, emittance, thread);
		if (vect_dot((*bounce_ray).dir, hit_info.normal) <= 0)
			return (false);
	}
	else if (hit_info.object->material.type == DIELECTRIC)
	{
		(*bounce_ray) = dielectric_scatter(hit_info, ray, emittance, thread);
	}
	else if (hit_info.object->material.type == GLOSSY)
	{
		float	cos = vect_dot(vect_simple_mult(ray.dir, -1.0), hit_info.normal);
		if (hit_info.object->material.specular > fast_rand(thread->state) 
			|| (reflectance(1.5, cos) > fast_rand(thread->state) && hit_info.object->material.specular))
		{
			(*bounce_ray) = metal_scatter(hit_info, ray, emittance, thread);
			if (vect_dot((*bounce_ray).dir, hit_info.normal) <= 0)
				return (false);
			hit_info.object->material.albedo = new_color(1.0, 1.0, 1.0);
		}
		else
		{
			(*bounce_ray) = lambertian_scatter(hit_info, emittance, thread);
		}
	}
	return (true);
}

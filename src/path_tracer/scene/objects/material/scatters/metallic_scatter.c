/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metallic_scatter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:16:07 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 19:33:02 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/sampling/light_sampling.h"
#include "path_tracer/thread_management/thread_management.h"
#include <stdint.h>
#include <math.h>

//Schlick's approximation
float	reflectance(float index, float cos)
{
	float	r;
	float	res;

	r = (1 - index) / (1 + index);
	r = r * r;
	res = r + (1 - r) * powf((1 - cos), 5);
	return (res);
}

t_ray	metal_scatter(t_hit_info hit_info, t_ray inc_ray,
	t_color *emittance, t_thread *thread)
{
	t_vect		bounce_dir;
	t_ray		bounce_ray;

	bounce_dir = vect_subtract(inc_ray.dir, vect_simple_mult(hit_info.normal,
				2 * vect_dot(inc_ray.dir, hit_info.normal)));
	if (hit_info.object->material.metal_roughness)
	{
		bounce_dir = vect_add(unit_vect(bounce_dir), vect_simple_mult(
					get_random_uvect(thread->state),
					powf(hit_info.object->material.metal_roughness, 2)));
	}
	bounce_ray = new_ray(bounce_dir, hit_info.point);
	hit_info.object->material.albedo = get_obj_color(&hit_info);
	*emittance = light_sampling(thread, hit_info, METAL);
	return (bounce_ray);
}

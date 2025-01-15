/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_sampling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:36:21 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 17:26:35 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/scene/scene.h"
#include "src/path_tracer/scene/ray/ray.h"
#include "src/path_tracer/utils/vectors/vectors.h"
#include "src/path_tracer/scene/objects/objects.h"
#include "src/path_tracer/scene/objects/material/material.h"
#include "src/path_tracer/thread_management/thread_management.h"
#include <math.h>

static float	p_light_specular(t_hit_info hit_info, t_ray inc_ray, t_vect cam_orientation)
{
	t_vect		bounce_dir;
	float		test;

	inc_ray.dir = unit_vect(inc_ray.dir);
	bounce_dir = vect_subtract(inc_ray.dir, vect_simple_mult(hit_info.normal, 2 * vect_dot(inc_ray.dir, hit_info.normal)));
	test = vect_dot(unit_vect(bounce_dir), cam_orientation);
	if (test < 0)
		test = 0;
	test = pow(test, (128 * (1.1 - hit_info.object->material.metal_roughness)));
	return (test);
}

static t_vect	test_sample_area(uint32_t *state, t_object *light)
{
	return (vect_add(light->get_origin(light), vect_simple_mult(get_random_uvect(state), light->figure.p_light.radius_shadow)));
}

t_color	light_sampling(t_thread *thread, t_hit_info hit_info, t_mat_type scatter_type)
{
	t_ray		shadow_ray;
	t_hit_info	test_hit;
	float		mod;
	float		mod2;
	t_object	*temp;
	t_color 	emittance;

	t_vect		bound_to_light;

	emittance = new_color(0.0, 0.0, 0.0);
	temp = thread->scene->lights;
	while (temp)
	{
		shadow_ray.origin = hit_info.point;
		bound_to_light = vect_subtract(temp->figure.p_light.location, hit_info.point);
		shadow_ray.dir = vect_subtract(test_sample_area(thread->state, temp), hit_info.point);
		if (!shadow_hit(thread->scene, shadow_ray, &test_hit, vect_length(bound_to_light)))
		{
			mod2 = 1 / vect_length(bound_to_light);
			if (scatter_type == LAMBERTIAN)
			{
				mod = vect_dot(hit_info.normal, unit_vect(bound_to_light));
				if (mod < 0)
					mod = 0;
				emittance = vect_add(emittance, vect_simple_mult(temp->material.color, (temp->material.emission_intensity * mod * mod2)));
			}
			else if (scatter_type == METAL)
				emittance = vect_add(emittance, vect_simple_mult(temp->material.color, (p_light_specular(hit_info, shadow_ray, thread->scene->camera.orientation) * temp->material.emission_intensity) * mod2 * 10));
		}
		temp = temp->next;
	}
	return (emittance);	
}

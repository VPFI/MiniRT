/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_sampling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:36:21 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 16:59:47 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/material/material.h"
#include "path_tracer/thread_management/thread_management.h"
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

static t_vect	sample_area(uint32_t *state, t_object *light)
{
	return (vect_add(light->get_origin(light), vect_simple_mult(get_random_uvect(state), light->figure.p_light.radius_shadow)));
}

static void	calc_material_emittance(t_thread *thread, t_hit_info hit_info, t_object *obj, t_mat_type scatter_type, t_vect *emittance)
{
	t_hit_info	test_hit;
	t_ray		shadow_ray;
	float		visual_angle;
	float		distance_decay;
	t_vect		bound_to_light;

	shadow_ray.origin = hit_info.point;
	shadow_ray.dir = vect_subtract(sample_area(thread->state, obj), hit_info.point);
	bound_to_light = vect_subtract(obj->figure.p_light.location, hit_info.point);
	if (!shadow_hit(thread->scene->objects, shadow_ray, &test_hit, vect_length(bound_to_light)))
	{
		distance_decay = 1 / vect_length(bound_to_light);
		if (scatter_type == LAMBERTIAN)
		{
			visual_angle = vect_dot(hit_info.normal, unit_vect(bound_to_light));
			if (visual_angle < 0)
				visual_angle = 0;
			(*emittance) = vect_add((*emittance), vect_simple_mult(obj->material.color,
				(obj->material.emission_intensity * visual_angle * distance_decay)));
		}
		else if (scatter_type == METAL)
			(*emittance) = vect_add((*emittance), vect_simple_mult(obj->material.color,
				(p_light_specular(hit_info, shadow_ray, thread->scene->camera.orientation)
				* obj->material.emission_intensity) * distance_decay * 10));
	}
}

t_color	light_sampling(t_thread *thread, t_hit_info hit_info, t_mat_type scatter_type)
{
	t_object	*obj;
	t_color 	emittance;

	emittance = new_color(0.0, 0.0, 0.0);
	obj = thread->scene->lights;
	while (obj)
	{
		hit_info.object = obj;
		calc_material_emittance();
		obj = obj->next;
	}
	return (emittance);
}

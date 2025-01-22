/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_sampling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:36:21 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 18:58:43 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/material/material.h"
#include "path_tracer/thread_management/thread_management.h"
#include <math.h>

static float	p_li_spec(t_hit_info hit_info,
	t_ray inc_ray, t_vect cam_orientation)
{
	t_vect		bounce_dir;
	float		test;

	inc_ray.dir = unit_vect(inc_ray.dir);
	bounce_dir = vect_subtract(inc_ray.dir,
			vect_simple_mult(hit_info.normal,
				2 * vect_dot(inc_ray.dir, hit_info.normal)));
	test = vect_dot(unit_vect(bounce_dir), cam_orientation);
	if (test < 0)
		test = 0;
	test = pow(test, (128 * (1.1 - hit_info.object->material.metal_roughness)));
	return (test);
}

static t_vect	sample_area(uint32_t *state, t_object *light)
{
	return (vect_add(
			light->get_origin(light),
			vect_simple_mult(
				get_random_uvect(state),
				light->figure.p_light.radius_shadow)));
}

static void	calc_material_emittance(t_thread *th, t_hit_info i,
	t_mat_type type, t_vect *em)
{
	float		d;
	float		angl;
	t_vect		l_dst;
	t_ray		shdw_r;
	t_hit_info	test_hit;

	shdw_r.origin = i.point;
	shdw_r.dir = vect_subtract(sample_area(th->state, i.object), i.point);
	l_dst = vect_subtract(i.object->figure.p_light.location, i.point);
	if (!shadow_hit(th->scene->objects, shdw_r, &test_hit, vect_length(l_dst)))
	{
		d = 1 / vect_length(l_dst);
		if (type == LAMBERTIAN)
		{
			angl = vect_dot(i.normal, unit_vect(l_dst));
			if (angl < 0)
				angl = 0;
			(*em) = vect_add((*em), vect_simple_mult(i.object->material.color,
						(i.object->material.emission_intensity * angl * d)));
		}
		else if (type == METAL)
			(*em) = vect_add((*em), vect_simple_mult(i.object->material.color,
						(p_li_spec(i, shdw_r, th->scene->camera.orientation)
							* i.object->material.emission_intensity) * d * 10));
	}
}

t_color	light_sampling(t_thread *thread, t_hit_info hit_info, t_mat_type type)
{
	t_object	*obj;
	t_color		emittance;

	emittance = new_color(0.0, 0.0, 0.0);
	obj = thread->scene->lights;
	while (obj)
	{
		hit_info.object = obj;
		calc_material_emittance(thread, hit_info, type, &emittance);
		obj = obj->next;
	}
	return (emittance);
}

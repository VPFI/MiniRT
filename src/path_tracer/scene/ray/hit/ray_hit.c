/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:25:44 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 15:55:58 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/scene/objects/objects.h"
#include <stdint.h>
#include <stdbool.h>

bool	ray_hit(t_object *objs, t_ray ray, t_hit_info *ht, t_object *sky_sphere)
{
	bool		hit;
	float		bounds[2];

	hit = false;
	bounds[MIN] = 0.001;
	if (sky_sphere)
		bounds[MAX] = sky_sphere->figure.sphere.radius;
	else
		bounds[MAX] = (float)(INT32_MAX - 10);
	while (objs)
	{
		if (objs->hit_func(ray, objs->figure, ht, bounds))
		{
			hit = true;
			bounds[MAX] = ht->t;
			ht->object = objs;
		}
		objs = objs->next;
	}
	return (hit);
}

static void	set_hit_record(t_object *objects, t_hit_info *hit_info,
	bool *hit, float bounds[2])
{
	*hit = true;
	bounds[MAX] = hit_info->t;
	hit_info->object = objects;
}

bool	ray_hit_plus_lights(t_object *objects,
	t_object *plights, t_ray ray, t_hit_info *hit_info)
{
	float	bounds[2];
	bool	hit;

	hit = false;
	bounds[MIN] = 0.001;
	bounds[MAX] = (float)(INT32_MAX - 10);
	while (objects)
	{
		if (objects->hit_func(ray, objects->figure, hit_info, bounds))
		{
			set_hit_record(objects, hit_info, &hit, bounds);
		}
		objects = objects->next;
	}
	while (plights)
	{
		if (plights->hit_func(ray, plights->figure, hit_info, bounds))
		{
			set_hit_record(plights, hit_info, &hit, bounds);
		}
		plights = plights->next;
	}
	return (hit);
}

bool	shadow_hit(t_object *objs, t_ray ray, t_hit_info *hit_info, float max)
{
	t_object	*temp;
	float		bounds[2];
	bool		hit;

	hit = false;
	bounds[MIN] = 0.001;
	bounds[MAX] = (float)(INT32_MAX - 10);
	if (max)
	{
		bounds[MAX] = max;
	}
	ray.dir = unit_vect(ray.dir);
	temp = objs;
	while (temp)
	{
		if (temp->hit_func(ray, temp->figure, hit_info, bounds))
		{
			hit = true;
			bounds[MAX] = hit_info->t;
			hit_info->object = temp;
			break ;
		}
		temp = temp->next;
	}
	return (hit);
}

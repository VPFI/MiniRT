/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/figures/disk/hit/hit.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/cylinder/utils/utils.h"
#include <math.h>

static bool	hit_cylinder_base(t_reference_system *ref_sys, t_figure fig, t_hit_info *internal_hit_info, float *bounds)
{
	t_figure		disk_figure;
	t_vect			base_center;

	ft_bzero(&disk_figure, sizeof(t_figure));
	disk_figure.disk.normal = new_vect(0.0, 0.0, 1.0);
	base_center = new_vect(0.0, 0.0, 0.0);
	base_center.z = ref_sys->center.z + (fig.cylinder.height * 0.5);
	disk_figure.disk.center = base_center;
	disk_figure.disk.radius = fig.cylinder.radius;
	if (!(hit_disk(ref_sys->ray, disk_figure, internal_hit_info, bounds)))
		return (false);
	bounds[MAX] = internal_hit_info->t;
	return (true);
}

static bool	cylinder_body_intersections(t_reference_system *ref_sys, t_figure fig, t_eq_params *params)
{
	t_vect		ray_to_cyl;

	ray_to_cyl = vect_subtract(ref_sys->center, ref_sys->ray.origin);
	ray_to_cyl.z = 0;
	params->a = (ref_sys->ray.dir.x * ref_sys->ray.dir.x)
		+ (ref_sys->ray.dir.y * ref_sys->ray.dir.y);
	params->b = -2.0 * ((ref_sys->ray.dir.x * ray_to_cyl.x)
			+ (ref_sys->ray.dir.y * ray_to_cyl.y));
	params->c = (ray_to_cyl.x * ray_to_cyl.x)
		+ (ray_to_cyl.y * ray_to_cyl.y) - (pow(fig.cylinder.radius, 2));
	params->discr = (params->b * params->b)	- (4.0 * params->a * params->c);
	if (params->discr < 0.0)
		return (false);
	params->root = (-params->b - sqrtf(params->discr)) / (2.0 * params->a);
	return (true);
}

static bool	hit_cylinder_body(t_reference_system *ref_sys, t_figure fig, t_hit_info *internal_hit_info, float *bounds)
{
	t_eq_params			params;
	t_vect				point;
	float				point_height;

	ft_bzero(&params, sizeof(t_eq_params));
	if (!(cylinder_body_intersections(ref_sys, fig, &params)))
		return (false);
	point = ray_at(ref_sys->ray, params.root);
	point_height = get_height(point, ref_sys->center, fig.cylinder.radius);
	if (params.root <= bounds[MIN] || params.root >= bounds[MAX]
		|| point_height > fig.cylinder.height / 2.0)
	{
		params.root = (-params.b + sqrtf(params.discr)) / (2.0 * params.a);
		point = ray_at(ref_sys->ray, params.root);
		point_height = get_height(point, ref_sys->center, fig.cylinder.radius);
		if (params.root <= bounds[MIN] || params.root >= bounds[MAX]
			|| point_height > fig.cylinder.height / 2.0)
		{
			return (false);
		}
	}
	internal_hit_info->t = params.root;
	internal_hit_info->point = ray_at(ref_sys->ray, internal_hit_info->t);
	bounds[MAX] = internal_hit_info->t;
	return (true);
}

bool	hit_cylinder(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	bool				hit;
	t_reference_system 	ref_sys;
	t_hit_info 			internal_hit_info;
	float 				internal_bounds[2];

	hit = false;
	internal_bounds[MIN] = bounds[MIN];
	internal_bounds[MAX] = bounds[MAX];	
	ft_bzero(&internal_hit_info, sizeof(t_hit_info));
	internal_hit_info.normal = new_vect(1.0, 0.0, 0.0);
	ref_sys.ray.origin = vect_subtract(ray.origin, fig.cylinder.center);
	ref_sys.ray.dir = ray.dir;
	ref_sys.center = new_vect(0.0, 0.0, 0.0);
	rotate_reference_system(fig.cylinder.normal, &ref_sys.ray.dir, &ref_sys.ray.origin);
	hit = hit_cylinder_base(&ref_sys, fig, &internal_hit_info, internal_bounds);
	hit |= hit_cylinder_body(&ref_sys, fig, &internal_hit_info, internal_bounds);
	fig.cylinder.height *= -1.0; // change this || figure pointer
	hit |= hit_cylinder_base(&ref_sys, fig, &internal_hit_info, internal_bounds);
	fig.cylinder.height *= -1.0;
	if (hit)
	{
		hit_info->t = internal_hit_info.t;
	}
	return (hit);
}

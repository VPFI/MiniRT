/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:07:29 by vperez-f         ###   ########.fr       */
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
#include <math.h>

static bool	cone_body_intersections(t_reference_system *ref,
	t_figure fig, t_eq_params *prms)
{
	float	hr_ratio;

	hr_ratio = fig.cone.height / fig.cone.radius;
	prms->a = ((hr_ratio * hr_ratio) * ((ref->ray.dir.x * ref->ray.dir.x)
				+ (ref->ray.dir.y * ref->ray.dir.y)))
		- (ref->ray.dir.z * ref->ray.dir.z);
	prms->b = 2.0 * (hr_ratio * ((hr_ratio * ref->ray.origin.x * ref->ray.dir.x)
				+ (ref->ray.dir.x * ref->center.x)
				+ (hr_ratio * ref->ray.origin.y * ref->ray.dir.y)
				+ (ref->ray.dir.y * ref->center.y))
			- (ref->ray.origin.z * ref->ray.dir.z)
			- (ref->ray.dir.z * ref->center.z));
	prms->c = pow(ref->center.x - (hr_ratio * ref->ray.origin.x), 2)
		+ pow(ref->center.y - (hr_ratio * ref->ray.origin.y), 2)
		- pow(ref->center.z - ref->ray.origin.z, 2);
	prms->discr = (prms->b * prms->b)
		- (4.0 * prms->a * prms->c);
	if (prms->discr < 0.0)
		return (false);
	prms->root = (-prms->b - sqrt(prms->discr))
		/ (2.0 * prms->a);
	return (true);
}

static bool	hit_cone_body(t_reference_system *ref_sys, t_figure fig,
	t_hit_info *internal_hit_info, float *bounds)
{
	t_eq_params			params;
	t_vect				point;
	float				point_height;

	ft_bzero(&params, sizeof(t_eq_params));
	if (!(cone_body_intersections(ref_sys, fig, &params)))
		return (false);
	point = ray_at(ref_sys->ray, params.root);
	point_height = point.z;
	if (params.root <= bounds[MIN] || params.root >= bounds[MAX]
		|| fabsf(point_height) > fig.cone.height || point_height < 0.0)
	{
		params.root = (-params.b + sqrtf(params.discr)) / (2.0 * params.a);
		point = ray_at(ref_sys->ray, params.root);
		point_height = point.z;
		if (params.root <= bounds[MIN] || params.root >= bounds[MAX]
			|| fabsf(point_height) > fig.cone.height || point_height < 0.0)
		{
			return (false);
		}
	}
	internal_hit_info->t = params.root;
	internal_hit_info->point = ray_at(ref_sys->ray, internal_hit_info->t);
	bounds[MAX] = internal_hit_info->t;
	return (true);
}

static bool	hit_cone_base(t_reference_system *ref_sys, t_figure fig,
	t_hit_info *internal_hit_info, float *bounds)
{
	t_figure		disk_figure;
	t_vect			base_center;

	ft_bzero(&disk_figure, sizeof(t_figure));
	disk_figure.disk.normal = new_vect(0.0, 0.0, 1.0);
	base_center = new_vect(0.0, 0.0, 0.0);
	base_center.z = ref_sys->center.z + (fig.cone.height);
	disk_figure.disk.center = base_center;
	disk_figure.disk.radius = fig.cone.radius;
	if (!(hit_disk(ref_sys->ray, disk_figure, internal_hit_info, bounds)))
		return (false);
	bounds[MAX] = internal_hit_info->t;
	return (true);
}

bool	hit_cone(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_reference_system 	ref;
	t_hit_info 			internal_hit_info;
	float 				internal_bounds[2];
	bool				hit;

	hit = false;
	internal_bounds[MIN] = bounds[MIN];
	internal_bounds[MAX] = bounds[MAX];	
	ft_bzero(&internal_hit_info, sizeof(t_hit_info));
	internal_hit_info.normal = new_vect(1.0, 0.0, 0.0);
	ref.ray.origin = vect_subtract(ray.origin, fig.cone.center);
	ref.ray.dir = ray.dir;
	ref.center = new_vect(0.0, 0.0, 0.0);
	rotate_reference_system(fig.cone.normal, &ref.ray.dir, &ref.ray.origin);
	hit = hit_cone_base(&ref, fig, &internal_hit_info, internal_bounds);
	hit |= hit_cone_body(&ref, fig, &internal_hit_info, internal_bounds);
	if (hit)
	{
		hit_info->t = internal_hit_info.t;
	}
	return (hit);
}

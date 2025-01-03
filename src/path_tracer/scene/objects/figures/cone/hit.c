/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:38:43 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


bool	cone_body_intersections(t_reference_system *ref_sys, t_figure fig, t_eq_params *params)
{
	float		hr_ratio;

	hr_ratio = fig.cone.height / fig.cone.radius;
	params->a = ((hr_ratio * hr_ratio) * ((ref_sys->ray.dir.x * ref_sys->ray.dir.x)
				+ (ref_sys->ray.dir.y * ref_sys->ray.dir.y)))
		- (ref_sys->ray.dir.z * ref_sys->ray.dir.z);
	params->b = 2.0 * (hr_ratio * ((hr_ratio * ref_sys->ray.origin.x * ref_sys->ray.dir.x)
				+ (ref_sys->ray.dir.x * ref_sys->center.x)
				+ (hr_ratio * ref_sys->ray.origin.y * ref_sys->ray.dir.y)
				+ (ref_sys->ray.dir.y * ref_sys->center.y))
			- (ref_sys->ray.origin.z * ref_sys->ray.dir.z)
			- (ref_sys->ray.dir.z * ref_sys->center.z));
	params->c = pow(ref_sys->center.x - (hr_ratio * ref_sys->ray.origin.x), 2)
		+ pow(ref_sys->center.y - (hr_ratio * ref_sys->ray.origin.y), 2)
		- pow(ref_sys->center.z - ref_sys->ray.origin.z, 2);
	params->discr = (params->b * params->b)
		- (4.0 * params->a * params->c);
	if (params->discr < 0.0)
		return (false);
	params->root = (-params->b - sqrt(params->discr))
		/ (2.0 * params->a);
	return (true);
}

bool	hit_cone_body(t_reference_system *ref_sys, t_figure fig, t_hit_info *internal_hit_info, float *bounds)
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

bool	hit_cone_base(t_reference_system *ref_sys, t_figure fig, t_hit_info *internal_hit_info, float *bounds)
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
	t_reference_system 	ref_sys;
	t_hit_info 			internal_hit_info;
	float 				internal_bounds[2];
	bool				hit;

	hit = false;
	internal_bounds[MIN] = bounds[MIN];
	internal_bounds[MAX] = bounds[MAX];	
	ft_bzero(&internal_hit_info, sizeof(t_hit_info));
	internal_hit_info.normal = new_vect(1.0, 0.0, 0.0);
	ref_sys.ray.origin = vect_subtract(ray.origin, fig.cone.center);
	ref_sys.ray.dir = ray.dir;
	ref_sys.center = new_vect(0.0, 0.0, 0.0);
	rotate_reference_system(fig.cone.normal, &ref_sys.ray.dir, &ref_sys.ray.origin);
	hit = hit_cone_base(&ref_sys, fig, &internal_hit_info, internal_bounds);
	hit |= hit_cone_body(&ref_sys, fig, &internal_hit_info, internal_bounds);
	if (hit)
	{
		hit_info->t = internal_hit_info.t;
	}
	return (hit);
}

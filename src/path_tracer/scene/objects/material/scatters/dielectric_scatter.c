/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dielectric_scatter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:16:34 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 14:21:23 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// η⋅sinθ=η′⋅sinθ′
t_ray	refract(t_hit_info hit_info, t_vect udir, float index, float cos)
{
	t_vect	perp;
	t_vect	parallel;
	t_ray	res;

	perp = vect_simple_mult(vect_add(udir, vect_simple_mult(hit_info.normal, cos)), index);
	parallel = vect_simple_mult(hit_info.normal, sqrtf(fabs(1.0 - vect_dot(perp, perp))) * -1.0);
	res = new_ray(vect_add(perp, parallel), hit_info.point);
	return (res);
}

t_ray	dielectric_scatter(uint32_t *state, t_hit_info hit_info, t_ray inc_ray, t_color *emittance, t_thread *thread)
{
	//check face vect_dot etc...
	t_ray		bounce_ray;
	bool		front_face;
	t_vect		udir;
	float		index;
	float		cos;
	float		sin;
	t_hit_info	adj_hit;

	adj_hit = hit_info;
	udir = unit_vect(inc_ray.dir);
	index = hit_info.object->material.refraction_index;
	front_face = vect_dot(hit_info.normal, udir) <= 0.0;
	if (front_face)
		index = AIR_REF_INDEX / index;
	else
		adj_hit.normal = vect_simple_mult(hit_info.normal, -1); //if not inverted + normal in point inception material
	cos = vect_dot(vect_simple_mult(udir, -1.0), adj_hit.normal);
	sin = sqrtf(1.0 - (cos * cos));
	if (((index * sin) > 1.0 || reflectance(index, cos) > fast_rand(state)) && front_face)
		bounce_ray = metal_scatter(state, adj_hit, inc_ray, emittance, thread);
	else
	{
		bounce_ray = refract(adj_hit, udir, index, cos);
		if (hit_info.object->material.metal_roughness)
			bounce_ray.dir = vect_add(unit_vect(bounce_ray.dir), vect_simple_mult(get_random_uvect(state), powf(hit_info.object->material.metal_roughness, 2)));
	}
	hit_info.object->material.albedo = get_obj_color(&hit_info);
	return (bounce_ray);
}

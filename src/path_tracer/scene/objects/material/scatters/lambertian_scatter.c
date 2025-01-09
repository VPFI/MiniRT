/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian_scatter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:16:18 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 14:17:14 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_ray	lambertian_scatter(uint32_t *state, t_hit_info hit_info, t_color *emittance, t_thread *thread)
{
	t_vect		bounce_dir;
	t_vect		target_on_sphere;
	t_ray		bounce_ray;

	bounce_dir = get_random_uvect(state);
	target_on_sphere = vect_add(bounce_dir, hit_info.normal);
	if (zero_vect(target_on_sphere))
		target_on_sphere = hit_info.normal;
	target_on_sphere = unit_vect(target_on_sphere); // = target_onsphere + hit.info.point
	bounce_ray = new_ray(target_on_sphere, hit_info.point);
	hit_info.object->material.albedo = get_obj_color(&hit_info);
	*emittance = light_sampling(thread, hit_info, LAMBERTIAN);
	return (bounce_ray);
}

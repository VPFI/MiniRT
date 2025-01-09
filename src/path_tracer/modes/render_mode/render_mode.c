/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:07 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 14:24:52 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	progressive_render(t_thread *thread, uint32_t x, uint32_t y, t_color color)
{
	t_color		final_color;
	t_vect		*prev_color_index;

	if ((x >= thread->scene->width) || y >= thread->scene->height)
		return ;
	prev_color_index = &thread->scene->cumulative_image[((y * thread->scene->image->width) + x)];
	prev_color_index->x += color.x;
	prev_color_index->y += color.y;
	prev_color_index->z += color.z;
	final_color = clamp_vect(vect_simple_mult(*prev_color_index, 1.0 / (float)thread->iterations), 0.0, 1.0);
	mlx_put_pixel(thread->scene->image, x, y, get_rgba(
		(int)(final_color.x * 255.9),
		(int)(final_color.y * 255.9),
		(int)(final_color.z * 255.9),
		255));
}

t_color	calc_pixel_color(t_thread *thread, t_ray ray, int depth)
{
	t_color		emittance;
	float		time_aux;
	t_hit_info	hit_info;
	t_ray		bounce_ray;

	float		rr_coef_test;

	if (depth <= (thread->scene->max_depth / 2))
		rr_coef_test = 0.8;
	else
		rr_coef_test = 1.0;
	if (depth < 1 || (rr_coef_test != 1.0 && fast_rand(thread->state) > rr_coef_test))
		return (new_color(0, 0, 0));
	ft_bzero(&hit_info, sizeof(hit_info));
	emittance = new_color(0, 0, 0);
	time_aux = mlx_get_time();
	if (ray_hit(thread->scene->objects, ray, &hit_info, thread->scene->sky_sphere))
	{
		hit_info.point = ray_at(ray, hit_info.t);
		hit_info.normal = hit_info.object->get_normal(&hit_info, &hit_info.object->figure);
		thread->time_hit += mlx_get_time() - time_aux;
		if (hit_info.object->material.type == EMISSIVE)
		{
			emittance = vect_simple_mult(get_obj_color(&hit_info), hit_info.object->material.emission_intensity);
			return (emittance);
		}
		if (!scatter_ray(thread, hit_info, &bounce_ray, ray, &emittance))
		{
			return (emittance);
		}
		emittance = vect_mult(emittance, get_obj_color(&hit_info));
		return (vect_simple_mult(vect_add(vect_mult(calc_pixel_color(thread, bounce_ray, depth - 1), get_obj_color(&hit_info)), emittance), 1 / rr_coef_test));
	}
	thread->time_hit += mlx_get_time() - time_aux;
	return (get_sky_color(thread, &ray));
}

void	render_mode(t_thread *thread, uint32_t x, uint32_t y)
{
	t_ray		ray;
	t_color		color;
	t_vect		pixel_offset;
	int			sample_count;

	sample_count = 0;
	color = new_color(0, 0, 0);
	while(sample_count < thread->scene->samples)
	{
		ray.origin = defocus_sample(thread->scene->camera, thread->state);
		pixel_offset = set_pixel_offset(thread->scene->camera, x, y, thread->state);
		ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
		thread->sampled = false;
		color = vect_add(color, calc_pixel_color(thread, ray, thread->scene->max_depth));
		sample_count++;
	}
	color = vect_simple_mult(color, 1 / (float)sample_count);
	progressive_render(thread, x, y, color);
}

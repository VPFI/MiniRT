/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:07 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/30 18:49:23 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




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
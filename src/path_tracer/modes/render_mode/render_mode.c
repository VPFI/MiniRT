/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:07 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 15:18:43 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "printf/ft_printf.h"
#include "path_tracer/path_tracer.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/export/export.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/scene/ray/scatter/ray_scatter.h"
#include "path_tracer/scene/camera/utils/camera_utils.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/math/math_utils.h"
#include "path_tracer/utils/color/color_utils.h"
#include "path_tracer/thread_management/thread_management.h"
#include "path_tracer/scene/background_color/background_color.h"
#include "window_management/key_identifiers/key_identifiers.h"

void	render_mode_hooks(t_scene *scene, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_X && is_press_and_ctrl(key_data))
	{
		stop_and_wait_threads(scene);
		scene->do_backup = true;
		if (export_to_ppm(scene->image))
			ft_printf(2, "Unexpected error exporting img | Resuming render\n");
		main_loop(scene);
	}
	else if (key_data.key == MLX_KEY_E && is_press_and_ctrl(key_data))
	{
		stop_and_wait_threads(scene);
		scene->edit_mode = true;
		ft_memset(scene->cumulative_image, 0,
			sizeof(t_vect) * scene->height * scene->width);
		main_loop(scene);
	}
}

static void	progressive_render(t_thread *th, uint32_t x,
	uint32_t y, t_color color)
{
	t_color		final_color;
	t_vect		*prev_color_index;

	if ((x >= th->scene->width) || y >= th->scene->height)
		return ;
	prev_color_index = &th->scene->cumulative_image
	[((y * th->scene->image->width) + x)];
	prev_color_index->x += color.x;
	prev_color_index->y += color.y;
	prev_color_index->z += color.z;
	final_color = clamp_vect(vect_simple_mult(*prev_color_index, 1.0
				/ (float)th->iterations), 0.0, 1.0);
	mlx_put_pixel(th->scene->image, x, y, get_rgba(
			(int)(final_color.x * 255.9),
			(int)(final_color.y * 255.9),
			(int)(final_color.z * 255.9),
			255));
}

static int	check_depth_and_rr(t_thread *thread, int depth, float *rr_coef)
{
	if (depth <= (thread->scene->max_depth / 2))
		*rr_coef = 0.8;
	else
		*rr_coef = 1.0;
	if (depth < 1 || (*rr_coef != 1.0 && fast_rand(thread->state) > *rr_coef))
		return (1);
	return (0);
}

static t_color	calc_pixel_color(t_thread *th, t_ray ray, int depth)
{
	t_hit_info	ht;
	t_color		emit;
	t_ray		b_ray;
	float		rr_coef;

	if (check_depth_and_rr(th, depth, &rr_coef))
		return (new_color(0, 0, 0));
	ft_bzero(&ht, sizeof(ht));
	emit = new_color(0, 0, 0);
	if (ray_hit(th->scene->objects, ray, &ht, th->scene->sky_sphere))
	{
		ht.point = ray_at(ray, ht.t);
		ht.normal = ht.object->get_normal(&ht, &ht.object->figure);
		if (!scatter_ray(th, ht, &b_ray, ray, &emit))
			return (emit);
		emit = vect_mult(emit, get_obj_color(&ht));
		return (vect_simple_mult(vect_add(vect_mult(
						calc_pixel_color(th, b_ray, depth - 1),
						get_obj_color(&ht)), emit), 1 / rr_coef));
	}
	return (get_background_color(th, &ray));
}

void	render_mode(t_thread *th, uint32_t x, uint32_t y)
{
	t_ray		ray;
	t_color		color;
	t_vect		pixel_offset;
	int			sample_count;

	sample_count = 0;
	color = new_color(0, 0, 0);
	while (sample_count < th->scene->samples)
	{
		ray.origin = defocus_sample(th->scene->camera, th->state);
		pixel_offset = set_pixel_offset(th->scene->camera, x, y, th->state);
		ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
		th->sampled = false;
		color = vect_add(
				color, calc_pixel_color(th, ray, th->scene->max_depth));
		sample_count++;
	}
	color = vect_simple_mult(color, 1 / (float)sample_count);
	progressive_render(th, x, y, color);
}

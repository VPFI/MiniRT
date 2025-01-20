/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:02:34 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 15:37:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/sphere/utils/utils.h"
#include "path_tracer/utils/color/color_utils.h"
#include "path_tracer/thread_management/thread_management.h"
#include "path_tracer/utils/math/math_utils.h"
#include <math.h>

static void	set_sky_texture_color(t_vect *point, t_figure *fig,
	t_texture *tx, t_color *color)
{
	float		polar_coords[2];
	t_vect		texture_dims;
	uint8_t		*pixel;
	t_texel		texel;
	float		point_radius;

	set_polar_coords(point, fig, polar_coords);
	point_radius = sqrt(pow(point->x, 2) + pow(point->z, 2));
	texture_dims.x = tx->texture->width * (point_radius / fig->sphere.radius);
	texture_dims.y = tx->texture->height;
	if (point->x < 0.0)
		polar_coords[LATITUDE] = -polar_coords[LATITUDE];
	if (point->y > 0.0)
		polar_coords[LONGITUDE] = -polar_coords[LONGITUDE];
	texel.x = (polar_coords[LATITUDE] * (tx->texture->width / texture_dims.x));
	texel.y = polar_coords[LONGITUDE] + (texture_dims.y / 2.0);
	if (polar_coords[LATITUDE] < 0)
		texel.x += tx->texture->width;
	texel.x = f_clamp(texel.x, 0, tx->texture->width - 1);
	texel.y = f_clamp(texel.y, 0, tx->texture->height - 1);
	pixel = tx->texture->pixels
		+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	color->x = *pixel / 255.0;
	color->y = *(pixel + 1) / 255.0;
	color->z = *(pixel + 2) / 255.0;
}

static t_color	get_skysphere_color(t_object *sky_sphere, t_hit_info *ht)
{
	t_color	scene_sky_color;
	t_vect	translated_pt;

	translated_pt = vect_subtract(ht->point, sky_sphere->figure.sphere.center);
	set_sky_texture_color(&translated_pt, &sky_sphere->figure,
		sky_sphere->texture, &scene_sky_color);
	return (scene_sky_color);
}

t_color	get_background_color(t_thread *thread, t_ray *ray)
{
	float		li;
	t_hit_info	hit_info;
	t_vect		background;

	ft_bzero(&hit_info, sizeof(hit_info));
	background = new_color(0.0, 0.0, 0.0);
	if (thread->scene->sky_sphere
		&& ray_hit(thread->scene->sky_sphere, *ray, &hit_info, NULL))
	{
		hit_info.point = ray_at(*ray, hit_info.t);
		background = get_skysphere_color(thread->scene->sky_sphere, &hit_info);
	}
	else
	{
		if (AMB)
			background = hexa_to_vect(thread->scene->amb_color);
		else
		{
			li = 0.5 * (ray->dir.y + 1.0);
			background = vect_add(vect_simple_mult(new_color(1, 1, 1), 1 - li),
					vect_simple_mult(new_color(0.3, 0.7, 1), li));
		}
	}
	background = vect_simple_mult(background, thread->scene->amb_light);
	return (background);
}

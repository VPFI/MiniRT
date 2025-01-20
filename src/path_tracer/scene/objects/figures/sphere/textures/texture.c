/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:34:54 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/texture/texture_objects.h"
#include "path_tracer/scene/objects/figures/sphere/utils/utils.h"
#include "path_tracer/utils/math/math_utils.h"
#include <math.h>

static void	remove_point_texture_offset_sphere(t_vect *point,
	float *polar_coords, t_vect *tex_dims)
{
	if (point->x < 0.0)
		polar_coords[LATITUDE] = -polar_coords[LATITUDE] + tex_dims->x
			+ (tex_dims->x * (int)(polar_coords[LATITUDE] / tex_dims->x));
	if (point->y > 0.0)
		polar_coords[LONGITUDE] = -polar_coords[LONGITUDE] + tex_dims->y
			+ (tex_dims->y * (int)(polar_coords[LONGITUDE] / tex_dims->y));
	if (polar_coords[LATITUDE] >= tex_dims->x)
		polar_coords[LATITUDE] = polar_coords[LATITUDE]
			- (tex_dims->x * (int)(polar_coords[LATITUDE] / tex_dims->x));
	if (polar_coords[LONGITUDE] >= tex_dims->y)
		polar_coords[LONGITUDE] = polar_coords[LONGITUDE]
			- (tex_dims->y * (int)(polar_coords[LONGITUDE] / tex_dims->y));
}

static void	rotate_texture_normal_sphere(t_vect *point, t_vect *normal)
{
	t_vect	point_normal;

	point_normal = unit_vect(*point);
	rotate_texture_normal(&point_normal, normal);
}

static void	set_bump_map_normal_sphere(t_hit_info *ht,
	t_vect *point, t_texture *tx, t_vect *normal)
{
	t_texel	texel;
	uint8_t	*pixel;
	float	p_r;
	t_vect	tex;
	float	polar_coord[2];

	set_polar_coords(point, &ht->object->figure, polar_coord);
	p_r = sqrtf(pow(point->x, 2) + pow(point->z, 2));
	tex.x = tx->texture_dim * (p_r / ht->object->figure.sphere.radius);
	tex.y = tx->texture_dim * (tx->texture->height / (float)tx->texture->width);
	remove_point_texture_offset_sphere(point, polar_coord, &tex);
	texel.x = f_clamp(polar_coord[LATITUDE] * (tx->texture->width / tex.x),
			0.0, tx->texture->width - 1);
	texel.y = f_clamp(polar_coord[LONGITUDE] * (tx->texture->height / tex.y),
			0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels
		+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
	rotate_texture_normal_sphere(point, normal);
}

t_vect	get_sphere_texture(t_hit_info *ht, t_texture *texture)
{
	t_vect	texture_normal;
	t_vect	trans_point;

	trans_point = vect_subtract(ht->point, ht->object->figure.sphere.center);
	set_bump_map_normal_sphere(ht, &trans_point, texture, &texture_normal);
	return (texture_normal);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:26:56 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include "path_tracer/scene/objects/figures/disk/base/base.h"
#include "path_tracer/scene/objects/texture/texture_objects.h"
#include "path_tracer/utils/math/math_utils.h"
#include <math.h>

static void	remove_point_texture_offset_disk(t_vect *point,
	t_vect *text_dims, float *point_arc, float base_height)
{
	if (point->x < 0.0)
	{
		*point_arc = (-1 * (*point_arc)) + text_dims->x
			+ (text_dims->x * (int)(*point_arc / text_dims->x));
	}
	if (*point_arc >= text_dims->x)
	{
		*point_arc = *point_arc - (text_dims->x
				* (int)(*point_arc / text_dims->x));
	}
	if (0.0 < text_dims->y)
	{
		point->z = base_height;
	}
	if (base_height >= text_dims->y)
	{
		point->z = (base_height) - (text_dims->y
				* (int)((base_height) / text_dims->y));
	}
}

static void	set_bump_map_normal_disk(t_figure *fig, t_vect *point,
	t_vect *normal, t_texture *tx)
{
	t_base_params	bp;
	t_texel			texel;
	uint8_t			*pixel;
	t_vect			texture_dims;

	set_base_params(&bp, point, fig->disk.radius);
	texture_dims.x = tx->texture_dim
		* (bp.point_radius / fig->disk.radius);
	texture_dims.y = tx->texture_dim
		* (tx->texture->height / (float)tx->texture->width);
	remove_point_texture_offset_disk(point, &texture_dims,
		&bp.point_arc, bp.base_height);
	texel.x = f_clamp(bp.point_arc * (tx->texture->width / texture_dims.x),
			0.0, tx->texture->width - 1);
	texel.y = f_clamp(point->z * (tx->texture->height / texture_dims.y),
			0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels
		+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
}

t_vect	get_disk_texture(t_hit_info *hit_info, t_texture *tx, t_figure *fig)
{
	float			angle;
	t_vect			rotated_point;
	t_vect			texture_normal;

	rotated_point = vect_subtract(hit_info->point, fig->disk.center);
	angle = rotate_reference_system(fig->disk.normal, NULL, &rotated_point);
	set_bump_map_normal_disk(fig, &rotated_point, &texture_normal, tx);
	rotate_by_angle(&texture_normal, &fig->disk.normal, -angle);
	return (texture_normal);
}

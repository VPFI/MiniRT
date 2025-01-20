/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:41:18 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include "path_tracer/scene/objects/texture/texture_objects.h"
#include "path_tracer/utils/math/math_utils.h"
#include <math.h>

static void	remove_point_texture_offset_plane(t_vect *point, t_vect *text_dims)
{
	if (point->x < 0.0)
		point->x = point->x + text_dims->x
			+ (text_dims->x * (int)(fabs(point->x / text_dims->x)));
	if (point->y > 0.0)
		point->y = point->y - text_dims->y
			- (text_dims->y * (int)(point->y / text_dims->y));
	if (point->x >= text_dims->x)
		point->x = point->x
			- (text_dims->x * (int)(point->x / text_dims->x));
	if (fabs(point->y) >= text_dims->y)
		point->y = point->y
			+ (text_dims->y * (int)(fabs(point->y) / text_dims->y));
}

static void	set_bump_map_normal_plane(t_vect *pt, t_texture *tx, t_vect *norm)
{
	t_texel		texel;
	uint8_t		*pixel;
	t_vect		texture_dims;

	texture_dims.x = tx->texture_dim;
	texture_dims.y = tx->texture_dim
		* (tx->texture->height / (float) tx->texture->width);
	remove_point_texture_offset_plane(pt, &texture_dims);
	texel.x = f_clamp(pt->x * (tx->texture->width / texture_dims.x),
			0.0, tx->texture->width - 1);
	texel.y = f_clamp(fabs(pt->y) * (tx->texture->height / texture_dims.y),
			0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels
		+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*norm = translate_texture_to_normal(pixel);
}

t_vect	get_plane_texture(t_hit_info *hit_info, t_texture *tx, t_figure *fig)
{
	float	angle;
	t_vect	texture_normal;
	t_vect	rotated_point;

	rotated_point = vect_subtract(hit_info->point, fig->plane.center);
	angle = rotate_reference_system(fig->plane.normal, NULL, &rotated_point);
	set_bump_map_normal_plane(&rotated_point, tx, &texture_normal);
	rotate_by_angle(&texture_normal, &fig->plane.normal, -angle);
	return (texture_normal);
}

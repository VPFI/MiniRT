/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 17:31:28 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/utils/vectors/vectors.h"
#include "src/path_tracer/scene/objects/objects.h"
#include "src/path_tracer/utils/rotations/rotations.h"
#include "src/path_tracer/scene/objects/figures/figures.h"
#include "src/path_tracer/scene/objects/texture/texture_objects.h"
#include "src/path_tracer/utils/math/math_utils.h"
#include <math.h>

static void	remove_point_texture_offset_plane(t_vect *point, t_vect *texture_dims)
{
	if (point->x < 0.0)
		point->x = point->x + texture_dims->x
			+ (texture_dims->x * (int)(fabs(point->x / texture_dims->x)));
	if (point->y > 0.0)
		point->y = point->y - texture_dims->y
			- (texture_dims->y * (int)(point->y / texture_dims->y));
	if (point->x >= texture_dims->x)
		point->x = point->x
			- (texture_dims->x * (int)(point->x / texture_dims->x));
	if (fabs(point->y) >= texture_dims->y)
		point->y = point->y
			+ (texture_dims->y * (int)(fabs(point->y) / texture_dims->y));
}

static void	set_bump_map_normal_plane(t_vect *point, t_texture *tx, t_vect *normal)
{
	t_texel		texel;
	uint8_t		*pixel;
	t_vect		texture_dims;

	texture_dims.x = tx->texture_dim;
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float) tx->texture->width);
	remove_point_texture_offset_plane(point, &texture_dims);
	texel.x = f_clamp(point->x * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(fabs(point->y) * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels	+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
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

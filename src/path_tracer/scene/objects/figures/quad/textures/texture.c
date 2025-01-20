/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:25:27 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/utils/rotations/rotations.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include "path_tracer/scene/objects/texture/texture_objects.h"
#include "path_tracer/utils/math/math_utils.h"
#include <math.h>

static void	remove_point_texture_offset_quad(t_vect *point, t_vect *text_dims)
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

static void	set_bump_map_normal_quad(t_vect *point, t_texture *tx, t_vect *norm)
{
	t_texel		texel;
	uint8_t		*pixel;
	t_vect		texture_dims;

	texture_dims.x = tx->texture_dim;
	texture_dims.y = tx->texture_dim * (tx->texture->height
			/ (float) tx->texture->width);
	remove_point_texture_offset_quad(point, &texture_dims);
	texel.x = f_clamp(point->x * (tx->texture->width / texture_dims.x),
			0.0, tx->texture->width - 1);
	texel.y = f_clamp(fabs(point->y) * (tx->texture->height / texture_dims.y),
			0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels + ((4 * tx->texture->width) * texel.y)
		+ (4 * texel.x);
	*norm = translate_texture_to_normal(pixel);
}

t_vect	get_quad_texture(t_hit_info *hit_info, t_texture *tx, t_figure *fig)
{
	float	angle;
	float	aux_angle;
	t_vect	texture_normal;
	t_vect	rotated_point;
	t_vect	u_vect_rotated;

	u_vect_rotated = unit_vect(fig->quad.u_vect);
	rotate_reference_system(fig->quad.normal, &u_vect_rotated, NULL);
	u_vect_rotated = clamp_vect(u_vect_rotated, -1.0, 1.0);
	if (u_vect_rotated.y > 0.0)
		aux_angle = acos(-u_vect_rotated.x);
	else if (u_vect_rotated.y < 0.0)
		aux_angle = -acos(-u_vect_rotated.x);
	else
		aux_angle = 0.0;
	rotated_point = get_rotated_point_quad(hit_info);
	angle = rotate_reference_system(fig->quad.normal, NULL, NULL);
	set_bump_map_normal_quad(&rotated_point, tx, &texture_normal);
	rotate_vector(&texture_normal, new_vect(0.0, 0.0, 1.0), -aux_angle);
	rotate_by_angle(&texture_normal, &fig->quad.normal, -angle);
	return (texture_normal);
}

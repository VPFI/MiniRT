/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:05:36 by vperez-f         ###   ########.fr       */
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

static void	rotate_texture_normal_cone(t_vect *point,
	t_vect *normal, t_figure *fig)
{
	t_vect	axis;
	float	angle;
	t_vect	point_normal;

	point_normal = *point;
	point_normal.z = 0;
	point_normal = unit_vect(point_normal);
	axis = unit_vect(vect_cross(*point, point_normal));
	angle = sin(fig->cone.radius / hypot(fig->cone.radius, fig->cone.height));
	rotate_vector(&point_normal, axis, angle);
	point_normal = unit_vect(point_normal);
	rotate_texture_normal(&point_normal, normal);
}

static void	remove_point_texture_offset_cone(t_vect *point,
	float *arc, t_vect *text_dims)
{
	if (point->x < 0.0)
		*arc = -*arc + text_dims->x
				+ (text_dims->x * (int)(*arc / text_dims->x));
	if (point->z < 0.0)
		point->z = point->z + text_dims->y
				+ (text_dims->y * (int)(fabs(point->z) / text_dims->y));
	if (*arc >= text_dims->x)
		*arc = *arc	- (text_dims->x * (int)(*arc / text_dims->x));
	if (point->z >= text_dims->y)
		point->z = point->z	- (text_dims->y * (int)(point->z / text_dims->y));
}

static void	set_bump_map_normal_cone(t_vect *point, t_vect *normal,
	t_texture *tx, t_figure *fig)
{
	float	arc;
	t_texel	texel;
	uint8_t	*pixel;
	t_vect	texture_dims;
	float	point_radius;

	point_radius = point->z * (fig->cone.radius / fig->cone.height);
	texture_dims.x = tx->texture_dim * (point_radius / fig->cone.radius);
	texture_dims.y = tx->texture_dim
		* (tx->texture->height / (float) tx->texture->width);
	arc = get_point_angle(point) * point_radius;
	remove_point_texture_offset_cone(point, &arc, &texture_dims);
	texel.x = f_clamp(arc * (tx->texture->width / texture_dims.x),
			0.0, tx->texture->width - 1);
	texel.y = f_clamp(point->z * (tx->texture->height / texture_dims.y),
			0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels
		+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
	rotate_texture_normal_cone(point, normal, fig);
}

t_vect	get_cone_texture(t_hit_info *ht, t_texture *tx,
	t_figure *fig, int is_base)
{
	float	angle;
	t_vect	rotated_point;
	t_vect	texture_normal;

	rotated_point = vect_subtract(ht->point, fig->cone.center);
	angle = rotate_reference_system(fig->cone.normal, NULL, &rotated_point);
	if (is_base)
	{
		set_bump_map_normal_base(&rotated_point, &texture_normal,
			tx, fig->cone.radius, fig->cone.height);
	}
	else
	{
		set_bump_map_normal_cone(&rotated_point, &texture_normal, tx, fig);
	}
	rotate_by_angle(&texture_normal, &fig->cone.normal, -angle);
	return (texture_normal);
}

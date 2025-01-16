/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 19:14:59 by vperez-f         ###   ########.fr       */
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

static void	rotate_texture_normal_cylinder(t_vect *point, t_vect *normal)
{
	t_vect	point_normal;

	point_normal = *point;
	point_normal.z = 0;
	point_normal = unit_vect(point_normal);
	rotate_texture_normal(&point_normal, normal);
}

static void	remove_point_texture_offset_cylinder(t_vect *point, float *arc, t_vect *texture_dims)
{
	if (point->x < 0.0)
		*arc = -*arc + texture_dims->x + (texture_dims->x * (int)(*arc / texture_dims->x));
	if (point->z < 0.0)
		point->z = point->z + texture_dims->y + (texture_dims->y * (int)(fabs(point->z) / texture_dims->y));
	if (*arc >= texture_dims->x)
		*arc = *arc	- (texture_dims->x * (int)(*arc / texture_dims->x));
	if (point->z >= texture_dims->y)
		point->z = point->z	- (texture_dims->y * (int)(point->z / texture_dims->y));
}

static void	set_bump_map_normal_cylinder(t_vect *point, t_vect *normal, t_texture *tx, t_figure *fig)
{
	float	arc;
	float	angle;
	t_texel	texel;
	uint8_t	*pixel;
	t_vect	texture_dims;

	texture_dims.x = tx->texture_dim;
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float) tx->texture->width);
	angle = get_point_angle(point);
	arc = angle * fig->cylinder.radius;
	remove_point_texture_offset_cylinder(point, &arc, &texture_dims);
	texel.x = f_clamp(arc * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(point->z * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels + ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
	rotate_texture_normal_cylinder(point, normal);
}

t_vect	get_cylinder_texture(t_hit_info *ht, t_texture *tx, t_figure *fig, int is_base)
{
	float	angle;
	t_vect	axis;
	t_vect	rotated_point;
	t_vect	reverse_normal;
	t_vect	texture_normal;

	rotated_point = vect_subtract(ht->point, fig->cylinder.center);
	reverse_normal = vect_simple_mult(fig->cylinder.normal, -1.0);
	angle = rotate_reference_system(reverse_normal, NULL, &rotated_point);
	if (is_base)
	{
		set_bump_map_normal_base(&rotated_point, &texture_normal, tx, fig->cylinder.radius, (-fig->cylinder.height / 2) * is_base);
		if (is_base == 1)
		{
			axis = new_vect(0.0, 1.0, 0.0);
			rotate_by_angle(&texture_normal, &axis, M_PI);
		}
	}
	else
		set_bump_map_normal_cylinder(&rotated_point, &texture_normal, tx, fig);
	rotate_by_angle(&texture_normal, &reverse_normal, -angle);
	return (texture_normal);
}

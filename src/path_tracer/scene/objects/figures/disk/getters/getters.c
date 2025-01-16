/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 16:36:42 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/utils/vectors/vectors.h"
#include "src/path_tracer/scene/objects/objects.h"
#include "src/path_tracer/scene/objects/figures/figures.h"
#include "src/path_tracer/scene/objects/figures/shared.h"
#include "src/path_tracer/scene/objects/figures/disk/base/base.h"
#include "src/path_tracer/scene/objects/texture/texture_objects.h"
#include "src/path_tracer/scene/objects/figures/disk/textures/texture.h"
#include "src/path_tracer/utils/rotations/rotations.h"
#include <math.h>

t_vect	get_disk_pattern(t_hit_info *hit_info)
{	
	t_base_params	bp;
	t_pattern_vars	p_var;
	t_vect			rotated_point;
	float			point_pattern_dim;

	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.disk.center);
	rotate_reference_system(hit_info->object->figure.disk.normal, NULL, &rotated_point);
	set_base_params(&bp, &rotated_point, hit_info->object->figure.disk.radius);
	point_pattern_dim = bp.point_radius * (hit_info->object->material.pattern_dim / hit_info->object->figure.disk.radius);
	p_var.x_index_square = (int)(fabs(bp.point_arc)/ point_pattern_dim);
	p_var.y_index_square = (int)(fabs(bp.base_height) / hit_info->object->material.pattern_dim);
	if (rotated_point.x > 0.0)
		p_var.x_index_square++;
	if (rotated_point.z > 0.0 && fabs(rotated_point.z) > 0.0001)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(hit_info->object->material.color);
	else
		return(vect_simple_div(hit_info->object->material.color, 3.0));
}

t_vect	get_origin_disk(t_object *object)
{
	return (object->figure.disk.center);
}

t_vect	get_disk_normal(t_hit_info *hit_info, t_figure *fig)
{
	if (hit_info->object->texture)
	{
		return (get_disk_texture(hit_info, hit_info->object->texture, fig));
	}
	else
	{
		return (fig->disk.normal);
	}
}

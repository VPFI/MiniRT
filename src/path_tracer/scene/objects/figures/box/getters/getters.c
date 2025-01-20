/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:17:52 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/hooks/management/object_management.h"
#include "path_tracer/scene/objects/material/material.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/figures/shared.h"
#include "path_tracer/scene/objects/figures/box/utils/utils.h"
#include "error_management/error_management.h"
#include <math.h>

t_object	*get_box_face(t_hit_info *hit_info, int *face_index)
{
	t_vect		compare_vect;
	t_vect		normal;
	t_object	*face;

	face = hit_info->object->figure.box.faces;
	while (face)
	{
		compare_vect = vect_subtract(hit_info->point, face->get_origin(face));
		normal = unit_vect(vect_cross(face->figure.quad.u_vect,
				face->figure.quad.v_vect));
		if (fabsf(vect_dot(compare_vect, normal)) < 1e-4)
		{
			return (face);
		}
		if (face_index)
			(*face_index)++;
		face = face->next;
	}
	return (NULL);
}

t_vect	get_face_pattern(t_hit_info *hit_info, t_vect *dim, int face_index)
{
	t_pattern_vars	p_var;
	t_vect			rotated_point;

	rotated_point = get_rotated_point_quad(hit_info);
	p_var.x_index_square = (int)(fabs(rotated_point.x)
		/ hit_info->object->material.pattern_dim);
	p_var.y_index_square = (int)(fabs(rotated_point.y)
		/ hit_info->object->material.pattern_dim);
	if (rotated_point.x < 0.0)
		p_var.x_index_square++;
	if (rotated_point.y < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2)
		+ (p_var.y_index_square % 2)) % 2;
	p_var.pattern_index = correct_box_pattern_index(dim, face_index,
		p_var.pattern_index);
	if (p_var.pattern_index == 0)
	{
		return (hit_info->object->material.color);
	}
	else
	{
		return (vect_simple_div(hit_info->object->material.color, 3.0));
	}
}

t_vect	get_box_pattern(t_hit_info *hit_info)
{
	int			face_index;
	t_hit_info	face_hit_info;

	face_index = 0;
	if (hit_info->object->material.pattern)
	{
		face_hit_info = *hit_info;
		face_hit_info.object = get_box_face(hit_info, &face_index);
		face_hit_info.object->material.color = hit_info->object->material.color;
		if (face_hit_info.object)
		{
			return (get_face_pattern(&face_hit_info,
				&hit_info->object->figure.box.dimensions, face_index));
		}
		else
		{
			return (hit_info->object->material.color);
		}
	}
	else
	{
		return (hit_info->object->material.color);
	}
}

t_vect	get_origin_box(t_object *object)
{
	return (object->figure.box.center);
}

t_vect	get_box_normal(t_hit_info *hit_info, t_figure *fig)
{
	t_hit_info	face_ht;

	(void)fig;
	face_ht = *hit_info;
	face_ht.object = get_box_face(hit_info, NULL);
	return (face_ht.object->get_normal(&face_ht, &face_ht.object->figure));
}

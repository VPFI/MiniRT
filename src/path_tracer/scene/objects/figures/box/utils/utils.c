/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:48:26 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 15:39:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "src/path_tracer/utils/vectors/vectors.h"
#include "src/path_tracer/scene/objects/objects.h"
#include "src/path_tracer/scene/objects/figures/figures.h"
#include "src/path_tracer/scene/objects/texture/texture_objects.h"
#include "src/path_tracer/scene/objects/material/material.h"
#include "src/path_tracer/scene/objects/figures/quad/quad.h"
#include "src/error_management/error_management.h"

int	correct_box_pattern_index(t_vect *dimensions, int face_index, int pattern_index)
{
	if ((face_index == 2 || face_index == 3))
	{
		if (!((int)((dimensions->z - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;
		if (((int)((dimensions->x - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;		
	}
	if ((face_index == 4 || face_index == 5))
	{
		if (((int)((dimensions->z - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;
		if (((int)((dimensions->y - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;
	}
	return (pattern_index);
}

void	add_box_face(t_object *box, t_figure face, t_material mat)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	new_obj->type = QUAD;
	new_obj->figure.quad.center = face.quad.center;
	new_obj->figure.quad.u_vect = face.quad.u_vect;
	new_obj->figure.quad.v_vect = face.quad.v_vect;
	new_obj->figure.quad.normal = unit_vect(vect_cross(face.quad.u_vect, face.quad.v_vect));
	new_obj->material = mat;
	if (box->texture)
		new_obj->texture = get_texture(box->texture->path, box->texture->texture_dim);
	else
		new_obj->texture = NULL;
	new_obj->hit_func = hit_quad;
	new_obj->edit_origin = translate_quad;
	new_obj->edit_orientation = rotate_quad;
	new_obj->get_origin = get_origin_quad;
	new_obj->edit_dimensions = resize_quad;
	new_obj->get_visual = get_quad_pattern;
	new_obj->get_normal = get_quad_normal;
	new_obj->next = NULL;
	add_object(&box->figure.box.faces, new_obj);
}

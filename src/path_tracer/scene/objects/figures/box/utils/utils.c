/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:48:26 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:13:50 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include "path_tracer/scene/objects/texture/texture_objects.h"
#include "path_tracer/scene/objects/material/material.h"
#include "path_tracer/scene/objects/figures/quad/quad.h"
#include "error_management/error_management.h"

int	correct_box_pattern_index(t_vect *dimensions,
	int face_index, int pattern_index)
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
	t_object	*n;

	n = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!n)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	n->type = QUAD;
	n->figure.quad.center = face.quad.center;
	n->figure.quad.u_vect = face.quad.u_vect;
	n->figure.quad.v_vect = face.quad.v_vect;
	n->figure.quad.normal = unit_vect(
			vect_cross(face.quad.u_vect, face.quad.v_vect));
	n->material = mat;
	if (box->texture)
		n->texture = get_texture(box->texture->path, box->texture->texture_dim);
	else
		n->texture = NULL;
	n->hit_func = hit_quad;
	n->edit_origin = translate_quad;
	n->edit_orientation = rotate_quad;
	n->get_origin = get_origin_quad;
	n->edit_dimensions = resize_quad;
	n->get_visual = get_quad_pattern;
	n->get_normal = get_quad_normal;
	n->next = NULL;
	add_object(&box->figure.box.faces, n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:51:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/24 00:05:09 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/scene/objects/figures/figures_parser.h"
#include "path_tracer/scene/objects/figures/box/box.h"

void	load_box(t_scene *scene, char **cmp, int amount)
{
	t_figure	fig;
	t_material	mat;
	t_vect		normal;
	t_texture	*texture;

	texture = NULL;
	if (amount < 6)
	{
		exit_err(ERR_ATTR_MSG, "box | missing essential attributes\n", 2);
	}
	mat = new_standard_material();
	fig.box.center = input_to_vect(cmp[1], (float)INT_MIN, (float)INT_MAX);
	fig.box.u_vect = input_to_vect(cmp[2], (float)INT_MIN, (float)INT_MAX);
	fig.box.v_vect = input_to_vect(cmp[3], (float)INT_MIN, (float)INT_MAX);
	normal = unit_vect(vect_cross(fig.quad.u_vect, fig.quad.v_vect));
	if (zero_vect(normal))
		exit_err(ERR_EMPTY_MSG, "Normal can not be zeroes\n", 2);
	fig.box.dimensions = input_to_vect(cmp[4], (float)INT_MIN, (float)INT_MAX);
	mat.color = vect_simple_div(input_to_vect(cmp[5], 0, 255), 255.0);
	parse_extra_object_components(&mat, &texture, cmp, 6);
	init_box(scene, fig, mat, texture);
}

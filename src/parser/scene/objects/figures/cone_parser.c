/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:51:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/24 00:05:15 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/scene/objects/figures/figures_parser.h"
#include "path_tracer/scene/objects/figures/cone/cone.h"

void	load_cone(t_scene *scene, char **item, int amount)
{
	t_figure	fig;
	t_material	mat;
	t_texture	*texture;

	texture = NULL;
	if (amount < 6)
	{
		exit_err(ERR_ATTR_MSG, "cone | missing essential attributes\n", 2);
	}
	mat = new_standard_material();
	fig.cone.center = input_to_vect(item[1], (float)INT_MIN, (float)INT_MAX);
	fig.cone.normal = input_to_vect(item[2], (float)INT_MIN, (float)INT_MAX);
	if (zero_vect(fig.cone.normal))
		exit_err(ERR_EMPTY_MSG, "Normal can not be zeroes\n", 2);
	fig.cone.radius = ft_atof(item[3], 0, (float)INT_MAX);
	fig.cone.height = ft_atof(item[4], 0, (float)INT_MAX);
	mat.color = vect_simple_div(input_to_vect(item[5], 0, 255), 255.0);
	parse_extra_object_components(&mat, &texture, item, 6);
	init_cone(scene, fig, mat, texture);
}

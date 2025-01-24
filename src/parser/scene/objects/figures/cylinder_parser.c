/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:51:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/24 00:05:19 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/scene/objects/figures/figures_parser.h"
#include "path_tracer/scene/objects/figures/cylinder/cylinder.h"

void	load_cylinder(t_scene *scene, char **comp, int amount)
{
	t_figure	f;
	t_material	mat;
	t_texture	*texture;

	texture = NULL;
	if (amount < 6)
	{
		exit_err(ERR_ATTR_MSG, "cylinder | missing essential attributes\n", 2);
	}
	mat = new_standard_material();
	f.cylinder.center = input_to_vect(comp[1], (float)INT_MIN, (float)INT_MAX);
	f.cylinder.normal = input_to_vect(comp[2], (float)INT_MIN, (float)INT_MAX);
	if (zero_vect(f.cylinder.normal))
		exit_err(ERR_EMPTY_MSG, "Normal can not be zeroes\n", 2);
	f.cylinder.radius = ft_atof(comp[3], 0, (float)INT_MAX);
	f.cylinder.height = ft_atof(comp[4], 0, (float)INT_MAX);
	mat.color = vect_simple_div(input_to_vect(comp[5], 0, 255), 255.0);
	parse_extra_object_components(&mat, &texture, comp, 6);
	init_cylinder(scene, f, mat, texture);
}

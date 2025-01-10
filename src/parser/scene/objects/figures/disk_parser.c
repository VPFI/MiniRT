/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:51:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/10 18:41:27 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/parser/scene/objects/figures/figures_parser.h"
#include "src/path_tracer/scene/objects/figures/disk/setters.h"

void	load_disk(t_scene *scene, char **components, int amount)
{
	t_figure	fig;
	t_material	mat;
	t_texture	*texture;

	texture = NULL;
	if (amount < 5)
	{
		exit_err(ERR_ATTR_MSG, "disk | missing essential attributes\n", 2);
	}
	mat = new_standard_material();
	fig.disk.center = input_to_vect(components[1], (float)INT_MIN, (float)INT_MAX);
	fig.disk.normal = input_to_vect(components[2], (float)INT_MIN, (float)INT_MAX);
	if (zero_vect(fig.disk.normal))
		exit_err(ERR_EMPTY_MSG, "Normal can not be zeroes\n", 2);
	fig.disk.radius = ft_atof(components[3], 0, (float)INT_MAX);
	mat.color = vect_simple_div(input_to_vect(components[4], 0, 255), 255.0);
	mat.albedo = mat.color;
	parse_extra_object_components(&mat, &texture, components, 5);
	init_disk(scene, fig, mat, texture);
}

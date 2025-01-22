/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:51:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 15:12:45 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/scene/objects/figures/figures_parser.h"
#include "path_tracer/scene/objects/figures/disk/disk.h"

void	load_disk(t_scene *scene, char **comp, int amount)
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
	fig.disk.center = input_to_vect(comp[1], (float)INT_MIN, (float)INT_MAX);
	fig.disk.normal = input_to_vect(comp[2], (float)INT_MIN, (float)INT_MAX);
	if (zero_vect(fig.disk.normal))
		exit_err(ERR_EMPTY_MSG, "Normal can not be zeroes\n", 2);
	fig.disk.radius = ft_atof(comp[3], 0, (float)INT_MAX);
	mat.color = vect_simple_div(input_to_vect(comp[4], 0, 255), 255.0);
	mat.albedo = mat.color;
	parse_extra_object_components(&mat, &texture, comp, 5);
	init_disk(scene, fig, mat, texture);
}

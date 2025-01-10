/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:51:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/10 18:41:54 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/parser/scene/objects/figures/figures_parser.h"
#include "src/path_tracer/scene/objects/figures/sphere/setters.h"

void	load_sphere(t_scene *scene, char **components, int amount)
{
	t_figure	fig;
	t_material	mat;
	t_texture	*texture;

	texture = NULL;
	if (amount < 4)
	{
		exit_err(ERR_ATTR_MSG, "sphere | missing essential attributes\n", 2);
	}
	mat = new_standard_material();
	fig.sphere.center = input_to_vect(components[1], (float)INT_MIN, (float)INT_MAX);
	fig.sphere.radius = ft_atof(components[2], 0, (float)INT_MAX);
	mat.color = vect_simple_div(input_to_vect(components[3], 0, 255), 255.0);
	mat.albedo = mat.color;
	parse_extra_object_components(&mat, &texture, components, 4);
	init_sphere(scene, fig, mat, texture);
}

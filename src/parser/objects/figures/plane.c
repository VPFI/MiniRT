/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:51:52 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/24 17:07:16 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	load_plane(t_scene *scene, char **components, int amount)
{
	t_figure	fig;
	t_material	mat;
	t_texture	*texture;

	texture = NULL;
	if (amount < 4)
	{
		exit_err(ERR_ATTR_MSG, "plane | missing essential attributes\n", 2);
	}
	mat = new_standard_material();
	fig.plane.center = input_to_vect(components[1], (float)INT_MIN, (float)INT_MAX);
	fig.plane.normal = input_to_vect(components[2], (float)INT_MIN, (float)INT_MAX);
	if (zero_vect(fig.plane.normal))
		exit_err(ERR_EMPTY_MSG, "Normal can not be zeroes\n", 2);
	mat.color = vect_simple_div(input_to_vect(components[3], 0, 255), 255.0);
	mat.albedo = mat.color;
	parse_extra_object_components(&mat, &texture, components, 4);
	init_plane(scene, fig, mat, texture);
}

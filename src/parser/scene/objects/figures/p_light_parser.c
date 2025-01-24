/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_light_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:57:11 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/24 00:05:31 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/scene/objects/figures/figures_parser.h"
#include "path_tracer/scene/objects/figures/p_light/p_light.h"

void	load_p_light(t_scene *scene, char **comp, int amount)
{
	t_figure	f;
	t_material	mat;

	if (amount < 5)
	{
		exit_err(ERR_ATTR_MSG,
			"point light | missing essential attributes\n", 2);
	}
	mat = new_standard_plight();
	f.p_light.location = input_to_vect(comp[1], (float)INT_MIN, (float)INT_MAX);
	f.p_light.radius_shadow = ft_atof(comp[2], 0, (float)INT_MAX);
	mat.color = vect_simple_div(input_to_vect(comp[3], 0, 255), 255.0);
	mat.emission_intensity = ft_atof(comp[4], 0, (float)INT_MAX);
	init_p_light(scene, f, mat);
}

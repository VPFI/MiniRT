/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:44:46 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/23 20:46:29 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/scene.h"
#include "parser/utils/numerical_utils.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "error_management/error_management.h"
#include "path_tracer/utils/color/color_utils.h"

void	load_ambient(t_scene *scene, char **components, int amount)
{
	if (scene->ambient_set)
	{
		exit_err(ERR_EMPTY_MSG, "Cannot define ambient multiple times\n", 2);
	}
	if (amount < 3)
	{
		exit_err(ERR_ATTR_MSG, "ambient | missing essential attributes\n", 2);
	}
	scene->amb_light = ft_atof(components[1], 0, 1);
	scene->amb_color = vect_to_int(vect_simple_div(
				input_to_vect(components[2], 0, 255), 255.0));
	scene->ambient_set = 1;
}

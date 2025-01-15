/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:44:46 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/14 19:37:18 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "src/path_tracer/scene/scene.h"
#include "src/parser/utils/numerical_utils.h"
#include "src/path_tracer/utils/vectors/vectors.h"
#include "src/error_management/error_management.h"
#include "src/path_tracer/utils/color/color_utils.h"

void	load_ambient(t_scene *scene, char **components, int amount)
{
	if (amount < 3)
	{
		exit_err(ERR_ATTR_MSG, "ambient | missing essential attributes\n", 2);
	}
	if (scene->amb_light != -1)
		exit_err(ERR_EMPTY_MSG, "Cannot define ambient multiple times\n", 2);
	scene->amb_light = ft_atof(components[1], 0, 1);
	scene->amb_color = vect_to_int(vect_simple_div(input_to_vect(components[2], 0, 255), 255.0));
}

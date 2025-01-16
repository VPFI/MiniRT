/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:44:18 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/scene/camera/camera_parser.h"
#include "parser/utils/numerical_utils.h"
#include "parser/utils/lexical_utils.h"
#include "error_management/error_management.h"
#include "libft/libft.h"
#include <limits.h>

static void	load_extra_camera_components(char **settings, t_scene *scene)
{
	int	amount;

	amount = count_components(settings);
	if (amount != 3)
		exit_err(ERR_EMPTY_MSG, "Missing material components\n", 2);
	scene->camera.focus_dist = ft_atof(settings[1], 1, (float)INT_MAX);
	scene->camera.defocus_angle = ft_atof(settings[2], 0, 100);	
}

static void	parse_extra_camera_components(t_scene *scene, char **components, int i)
{
	char	**unit;

	while (components[i])
	{
		unit = ft_split(components[i], ':');
		if (!unit)
			exit_err(ERR_ATTR_MSG, "extra camera components\n", 2);
		if (!ft_strcmp(unit[0], "camera") || !ft_strcmp(unit[0], "cam"))
		{
			load_extra_camera_components(unit, scene);
		}
		ft_free_arr(unit);
		i++;
	}	
}

void	load_camera(t_scene *scene, char **components, int amount)
{
	if (amount < 4)
	{
		exit_err(ERR_ATTR_MSG, "camera | missing essential attributes\n", 2);
	}
	if (!zero_vect(scene->camera.orientation) || !zero_vect(scene->camera.origin) || scene->camera.fov)
		exit_err(ERR_EMPTY_MSG, "Cannot define camera multiple times\n", 2);
	scene->camera.origin = input_to_vect(components[1], (float)INT_MIN, (float)INT_MAX);
	scene->camera.orientation = unit_vect(input_to_vect(components[2], (float)INT_MIN, (float)INT_MAX));
	if (zero_vect(scene->camera.orientation))
		exit_err(ERR_EMPTY_MSG, "Normal can not be zeroes\n", 2);
	scene->camera.fov = ft_atof(components[3], 0, 180);
	scene->camera.focus_dist = FOCUS_DIST;
	scene->camera.defocus_angle = DEFOCUS;
	parse_extra_camera_components(scene, components, 4);
}

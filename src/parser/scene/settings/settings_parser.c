/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:44:54 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/scene/settings/settings_parser.h"
#include "error_management/error_management.h"
#include "parser/utils/numerical_utils.h"
#include "parser/utils/lexical_utils.h"
#include "path_tracer/scene/scene.h"
#include "libft/libft.h"
#include <limits.h>

static void	parse_spp(char **settings, t_scene *scene)
{
	int	amount;

	amount = count_components(settings);
	if (amount != 2)
		exit_err(ERR_EMPTY_MSG, "Missing samples components\n", 2);
	scene->samples = (int)ft_atof(settings[1], 0, (float)INT_MAX);
}

static void	parse_depth(char **settings, t_scene *scene)
{
	int	amount;

	amount = count_components(settings);
	if (amount != 2)
		exit_err(ERR_EMPTY_MSG, "Missing depth components\n", 2);
	scene->max_depth = (int)ft_atof(settings[1], 0, (float)INT_MAX);
}

static void	parse_skysphere(char **settings, t_scene *scene)
{
	int	amount;

	amount = count_components(settings);
	if (amount != 2)
		exit_err(ERR_EMPTY_MSG, "Missing skyphere components\n", 2);
	init_sky_sphere(scene, settings[1]);
}

static void	parse_extra_settings(t_scene *scene, char **components, int i)
{
	char	**unit;

	while (components[i])
	{
		unit = ft_split(components[i], ':');
		if (!unit)
			exit_err(ERR_ATTR_MSG, "extra scene components\n", 2);
		if (!ft_strcmp(unit[0], "spp"))
		{
			parse_spp(unit, scene);
		}
		else if (!ft_strcmp(unit[0], "depth"))
		{
			parse_depth(unit, scene);
		}
		else if (!ft_strcmp(unit[0], "skysphere") || !ft_strcmp(unit[0], "skybox"))
		{
			parse_skysphere(unit, scene);
		}
		ft_free_arr(unit);
		i++;
	}	
}

void	load_settings(t_scene *scene, char **components, int amount)
{
	if (amount < 1)
	{
		exit_err(ERR_ATTR_MSG, "scene | missing essential attributes\n", 2);
	}
	parse_extra_settings(scene, components, 1);
}

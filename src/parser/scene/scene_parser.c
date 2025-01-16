/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:45:58 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser/scene/scene_parser.h"
#include "parser/scene/ambient/ambient_parser.h"
#include "parser/scene/camera/camera_parser.h"
#include "parser/scene/settings/settings_parser.h"

int	parse_scene(t_scene *scene, char **components, int amount)
{
	if (!ft_strcmp(components[0], CAMERA_ID))
		load_camera(scene, components, amount);
	else if (!ft_strcmp(components[0], AMBIENT_ID))
		load_ambient(scene, components, amount);
	else if (!ft_strcmp(components[0], SETTINGS_ID))
		load_settings(scene, components, amount);
	else
		return (1);
	return (0);
}

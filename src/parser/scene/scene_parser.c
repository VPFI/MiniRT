/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:45:58 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 22:20:20 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/parser/scene/scene_parser.h"

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

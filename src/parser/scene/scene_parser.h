/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:19:19 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 22:20:07 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_PARSER_H
# define SCENE_PARSER_H

#include "src/path_tracer/scene/scene.h"

# define CAMERA_ID			"C"
# define AMBIENT_ID			"A"
# define SETTINGS_ID		"S"

int	parse_scene(t_scene *scene, char **components, int amount);

#endif
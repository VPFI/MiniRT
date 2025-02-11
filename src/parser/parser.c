/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:00:43 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 21:01:05 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/scene.h"
#include "parser/utils/lexical_utils.h"
#include "parser/scene/scene_parser.h"
#include "parser/scene/objects/objects_parser.h"
#include "error_management/error_management.h"

int	parse_components(t_scene *scene, char **components)
{
	int	amount;

	amount = count_components(components);
	if (!amount)
		return (1);
	if (parse_objects(scene, components, amount)
		&& parse_scene(scene, components, amount))
	{
		return (throw_err(ERR_NOID_MSG, components[0], 1));
	}
	return (0);
}

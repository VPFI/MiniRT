/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:56:04 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 15:24:35 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser/scene/objects/objects_parser.h"
#include "path_tracer/scene/objects/material/material.h"
#include "parser/scene/objects/figures/figures_parser.h"
#include "parser/scene/objects/texture/texture_parser.h"
#include "parser/scene/objects/material/material_parser.h"
#include "path_tracer/scene/objects/texture/texture_objects.h"
#include "error_management/error_management.h"

void	parse_extra_object_components(t_material *mat, t_texture **tx,
	char **components, int i)
{
	char	**unit;

	while (components[i])
	{
		unit = ft_split(components[i], ':');
		if (!unit)
			exit_err(ERR_ATTR_MSG, "extra material components\n", 2);
		if (!ft_strcmp(unit[0], "material") || !ft_strcmp(unit[0], "mat"))
		{
			parse_material(unit, mat);
		}
		else if (!ft_strcmp(unit[0], "pattern"))
		{
			parse_pattern(unit, mat);
		}
		else if (!ft_strcmp(unit[0], "texture") || !ft_strcmp(unit[0], "tx"))
		{
			parse_texture(unit, tx);
		}
		else
			exit_err(ERR_ATTR_MSG, "Unknown extra attribute identifier\n", 2);
		ft_free_arr(unit);
		i++;
	}
}

int	parse_objects(t_scene *scene, char **components, int amount)
{
	if (!ft_strcmp(components[0], SPHERE_ID))
		load_sphere(scene, components, amount);
	else if (!ft_strcmp(components[0], PLANE_ID))
		load_plane(scene, components, amount);
	else if (!ft_strcmp(components[0], QUAD_ID))
		load_quad(scene, components, amount);
	else if (!ft_strcmp(components[0], DISK_ID))
		load_disk(scene, components, amount);
	else if (!ft_strcmp(components[0], BOX_ID))
		load_box(scene, components, amount);
	else if (!ft_strcmp(components[0], CYLINDER_ID))
		load_cylinder(scene, components, amount);
	else if (!ft_strcmp(components[0], CONE_ID))
		load_cone(scene, components, amount);
	else if (!ft_strcmp(components[0], P_LIGHT_ID))
		load_p_light(scene, components, amount);
	else
		return (1);
	return (0);
}

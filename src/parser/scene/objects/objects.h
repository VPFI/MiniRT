/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:01:53 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 22:15:41 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "src/path_tracer/scene/scene.h"

# define SPHERE_ID			"sp"
# define PLANE_ID			"pl"
# define QUAD_ID			"qu"
# define DISK_ID			"di"
# define BOX_ID				"bx"
# define CYLINDER_ID		"cy"
# define CONE_ID			"co"
# define P_LIGHT_ID			"l"

int		parse_objects(t_scene *scene, char **components, int amount);

void	parse_extra_object_components(t_material *mat,
	t_texture **tx, char **components, int i);

#endif
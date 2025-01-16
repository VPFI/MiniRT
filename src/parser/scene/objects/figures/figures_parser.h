/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:13:28 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 19:14:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_PARSER_H
# define FIGURES_PARSER_H

# include "path_tracer/scene/scene.h"
# include "path_tracer/scene/objects/figures/figures.h"
# include "path_tracer/scene/objects/material/material.h"
# include "path_tracer/scene/objects/texture/texture_objects.h"
# include "error_management/error_management.h"
# include "parser/utils/numerical_utils.h"
# include "parser/utils/lexical_utils.h"
# include "parser/scene/objects/objects_parser.h"
# include <limits.h>

void	load_box(t_scene *scene, char **cmp, int amount);
void	load_cone(t_scene *scene, char **components, int amount);
void	load_disk(t_scene *scene, char **components, int amount);
void	load_quad(t_scene *scene, char **components, int amount);
void	load_plane(t_scene *scene, char **components, int amount);
void	load_sphere(t_scene *scene, char **components, int amount);
void	load_p_light(t_scene *scene, char **components, int amount);
void	load_cylinder(t_scene *scene, char **components, int amount);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:13:28 by vpf               #+#    #+#             */
/*   Updated: 2025/01/10 18:15:23 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_PARSER_H
# define FIGURES_PARSER_H

# include "src/path_tracer/scene/scene.h"
# include "src/path_tracer/scene/objects/figures/figures.h"
# include "src/path_tracer/scene/objects/material/material.h"
# include "src/path_tracer/scene/objects/texture/texture.h"
# include "src/error_management/error_management.h"
# include "src/parser/utils/numerical_utils.h"
# include "src/parser/utils/lexical_utils.h"
# include "src/parser/scene/objects/objects_parser.h"
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
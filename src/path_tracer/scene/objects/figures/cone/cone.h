/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:14 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 20:10:22 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "path_tracer/scene/scene.h"
# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/scene/objects/figures/figures.h"
# include "path_tracer/scene/objects/material/material.h"
# include "path_tracer/scene/objects/texture/texture_objects.h"

# include "path_tracer/scene/objects/figures/cone/hit/hit.h"
# include "path_tracer/scene/objects/figures/cone/utils/utils.h"
# include "path_tracer/scene/objects/figures/cone/getters/getters.h"
# include "path_tracer/scene/objects/figures/cone/textures/texture.h"
# include "path_tracer/scene/objects/figures/cone\
/transformations/transformations.h"

void	set_new_fig_cone(t_scene *scene, t_vect *offset_origin);
int		init_cone(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);

#endif
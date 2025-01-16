/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:14 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 17:50:31 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "src/path_tracer/scene/scene.h"
# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/scene/objects/figures/figures.h"
# include "src/path_tracer/scene/objects/material/material.h"
# include "src/path_tracer/scene/objects/texture/texture_objects.h"

# include "src/path_tracer/scene/objects/figures/plane/hit/hit.h"
# include "src/path_tracer/scene/objects/figures/plane/getters/getters.h"
# include "src/path_tracer/scene/objects/figures/plane/textures/texture.h"
# include "src/path_tracer/scene/objects/figures/plane/transformations/transformations.h"

void	set_new_fig_plane(t_scene *scene, t_vect *offset_origin);
int		init_plane(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);

#endif
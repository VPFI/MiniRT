/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:14 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 17:52:16 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "src/path_tracer/scene/scene.h"
# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/scene/objects/figures/figures.h"
# include "src/path_tracer/scene/objects/material/material.h"
# include "src/path_tracer/scene/objects/texture/texture_objects.h"

# include "src/path_tracer/scene/objects/figures/sphere/hit/hit.h"
# include "src/path_tracer/scene/objects/figures/sphere/utils/utils.h"
# include "src/path_tracer/scene/objects/figures/sphere/getters/getters.h"
# include "src/path_tracer/scene/objects/figures/sphere/textures/texture.h"
# include "src/path_tracer/scene/objects/figures/sphere/transformations/transformations.h"

void	set_new_fig_sphere(t_scene *scene, t_vect *offset_origin);
int		init_sphere(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);

#endif
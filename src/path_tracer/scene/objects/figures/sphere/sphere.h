/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:14 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 21:50:01 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "path_tracer/scene/scene.h"
# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/scene/objects/figures/figures.h"
# include "path_tracer/scene/objects/material/material.h"
# include "path_tracer/scene/objects/texture/texture_objects.h"

# include "path_tracer/scene/objects/figures/sphere/hit/hit.h"
# include "path_tracer/scene/objects/figures/sphere/utils/utils.h"
# include "path_tracer/scene/objects/figures/sphere/getters/getters.h"
# include "path_tracer/scene/objects/figures/sphere/textures/texture.h"
# include "path_tracer/scene/objects/figures/sphere/transformations/transformations.h"

void	init_sky_sphere(t_scene *scene, char *path);
void	set_new_fig_sphere(t_scene *scene, t_vect *offset_origin);
int		init_sphere(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);

#endif
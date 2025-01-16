/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_light.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:14 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:14:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_LIGHT_H
# define P_LIGHT_H

# include "path_tracer/scene/scene.h"
# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/scene/objects/figures/figures.h"
# include "path_tracer/scene/objects/material/material.h"

# include "path_tracer/scene/objects/figures/p_light/hit/hit.h"
# include "path_tracer/scene/objects/figures/p_light/getters/getters.h"
# include "path_tracer/scene/objects/figures/p_light/transformations/transformations.h"

void	set_new_fig_p_light(t_scene *scene, t_vect *offset_origin);
int		init_p_light(t_scene *scene, t_figure fig, t_material mat);

#endif
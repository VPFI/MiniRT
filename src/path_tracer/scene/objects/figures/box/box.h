/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:14 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 15:49:56 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_H
# define BOX_H

# include "src/path_tracer/scene/scene.h"
# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/scene/objects/figures/figures.h"
# include "src/path_tracer/scene/objects/texture/texture_objects.h"

# include "src/path_tracer/scene/objects/figures/box/hit/hit.h"
# include "src/path_tracer/scene/objects/figures/box/utils/utils.h"
# include "src/path_tracer/scene/objects/figures/box/getters/getters.h"
# include "src/path_tracer/scene/objects/figures/box/transformations/transformations.h"

void	set_new_fig_box(t_scene *scene, t_vect *offset_origin);
int		init_box(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);

#endif
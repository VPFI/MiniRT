/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:45:35 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:14:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_H
# define BASE_H

# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/scene/objects/figures/shared.h"
# include "path_tracer/scene/objects/figures/figures.h"
# include "path_tracer/scene/objects/texture/texture_objects.h"

void	set_base_params(t_base_params *params, t_vect *point, float radius);
int		belongs_to_base(t_vect point, t_vect center, t_vect normal, float height);
t_vect	get_base_pattern(t_vect *point, t_figure *figure, float pattern_dim, t_color *obj_color);
void	set_bump_map_normal_base(t_vect *point, t_vect *normal, t_texture *tx, float radius, float base_distance);
void	remove_point_texture_offset_base(t_vect *point,	t_vect *texture_dims, t_base_params *bp, float base_distance);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:28:34 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 16:46:30 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETTERS_H
# define GETTERS_H

# include "src/path_tracer/scene/objects/objects.h"
# include "src/path_tracer/utils/vectors/vectors.h"

t_vect	get_light_pattern(t_hit_info *hit_info);
t_vect	get_origin_point_light(t_object *object);
t_vect	get_light_normal(t_hit_info *hit_info, t_figure *fig);

#endif
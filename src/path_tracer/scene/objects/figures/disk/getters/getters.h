/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:28:34 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 21:36:30 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETTERS_H
# define GETTERS_H

# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/scene/objects/objects.h"

t_vect	get_origin_disk(t_object *object);
t_vect	get_disk_pattern(t_hit_info *hit_info);
t_vect	get_disk_normal(t_hit_info *hit_info, t_figure *fig);

#endif
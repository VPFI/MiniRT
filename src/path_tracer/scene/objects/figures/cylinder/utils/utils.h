/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:50 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 19:50:16 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/scene/objects/objects.h"
# include "path_tracer/scene/objects/figures/figures.h"

t_color	get_cylinder_body_pattern(t_hit_info *hit_info);
float	get_height(t_vect point, t_vect center, float base);
t_vect	compute_cylinder_normal(t_figure *fig, t_hit_info *ht, int is_base);

#endif
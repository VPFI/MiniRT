/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:07 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 19:26:24 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "path_tracer/scene/ray/ray.h"
# include "path_tracer/scene/objects/objects.h"
# include "path_tracer/scene/objects/figures/figures.h"

bool	hit_point_light(t_ray ray, t_figure fig, t_hit_info *ht, float *bounds);

#endif
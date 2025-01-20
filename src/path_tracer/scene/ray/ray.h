/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:18:43 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 14:50:38 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/scene/ray/hit/ray_hit.h"
# include "path_tracer/scene/ray/utils/ray_utils.h"
# include "path_tracer/scene/ray/scatter/ray_scatter.h"

typedef struct s_ray
{
	t_vect		origin;
	t_vect		dir;
}				t_ray;

t_ray	new_ray(t_vect dir, t_vect origin);

#endif
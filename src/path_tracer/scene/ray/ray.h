/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:18:43 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 17:24:23 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "src/path_tracer/utils/vectors/vectors.h"

typedef struct s_ray
{
	t_vect		origin;
	t_vect		dir;
}				t_ray;

# include "src/path_tracer/scene/ray/hit/ray_hit.h"
# include "src/path_tracer/scene/ray/utils/ray_utils.h"

t_ray	new_ray(t_vect dir, t_vect origin);

#endif
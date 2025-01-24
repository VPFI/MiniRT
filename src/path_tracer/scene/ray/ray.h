/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:18:43 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/24 00:48:10 by vpf              ###   ########.fr       */
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

typedef struct s_scatter_rays
{
	t_ray	inc_ray;
	t_ray	out_ray;
}			t_scatter_rays;

t_ray	new_ray(t_vect dir, t_vect origin);

#endif
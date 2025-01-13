/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:18:43 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/11 22:57:58 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "src/path_tracer/utils/vectors/vectors.h"

typedef struct s_ray
{
	t_vect		origin;
	t_vect		dir;
}				t_ray;

t_ray	new_ray(t_vect dir, t_vect origin);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:34:14 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 21:30:05 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATIONS_H
# define ROTATIONS_H

#include "src/path_tracer/scene/ray/ray.h"

typedef struct s_reference_system
{
	t_ray	ray;
	t_vect	center;
}			t_reference_system;

#endif
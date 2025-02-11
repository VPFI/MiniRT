/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:46 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 15:44:03 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/utils/vectors/vectors.h"

void	check_normal(t_vect *normal, t_vect *ray_dir)
{
	if (vect_dot(*normal, unit_vect(*ray_dir)) <= 0.0)
		return ;
	*normal = vect_simple_mult(*normal, -1.0);
}

t_vect	ray_at(t_ray ray, float pos)
{
	t_vect	res;

	res = vect_add(ray.origin, (vect_simple_mult(ray.dir, pos)));
	return (res);
}

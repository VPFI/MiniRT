/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:43:03 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 22:01:51 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"

t_vect	vect_add(t_vect vec, t_vect vec2)
{
	t_vect res;

	res.x = vec.x + vec2.x;
	res.y = vec.y + vec2.y;
	res.z = vec.z + vec2.z;
	return (res);
}

t_vect	vect_div(t_vect vec, t_vect vec2)
{
	t_vect res;

	res = new_vect(0.0f, 0.0f, 0.0f);
	if (vec2.x)
		res.x = vec.x / vec2.x;
	if (vec2.y)
		res.y = vec.y / vec2.y;
	if (vec2.z)
		res.z = vec.z / vec2.z;
	return (res);
}

t_vect	vect_mult(t_vect vec, t_vect vec2)
{
	t_vect res;

	res.x = vec.x * vec2.x;
	res.y = vec.y * vec2.y;
	res.z = vec.z * vec2.z;
	return (res);
}

t_vect	vect_subtract(t_vect vec, t_vect vec2)
{
	t_vect res;

	res.x = vec.x - vec2.x;
	res.y = vec.y - vec2.y;
	res.z = vec.z - vec2.z;
	return (res);
}
t_vect	vect_cross(t_vect vec, t_vect vec2)
{
	t_vect res;

	res.x = (vec.y * vec2.z) - (vec.z * vec2.y);
	res.y = (vec.z * vec2.x) - (vec.x * vec2.z);
	res.z = (vec.x * vec2.y) - (vec.y * vec2.x);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:09:48 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 22:00:29 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/utils/math/math_utils.h"
#include <math.h>

t_vect	unit_vect(t_vect vect)
{
	t_vect 	res;
	float	tot;

	tot = sqrtf(vect_dot(vect, vect));
	res.x = vect.x / tot;
	res.y = vect.y / tot;
	res.z = vect.z / tot;
	return (res);
}

bool	zero_vect(t_vect vect)
{
	float	threshold;

	threshold = 1e-8;
	return ((fabsf(vect.x) < threshold) && (fabsf(vect.y) < threshold) && (fabsf(vect.z) < threshold));
}

float	vect_length(t_vect vec)
{
	return (sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}

t_vect	clamp_vect( t_vect vect, float min, float max)
{
	if (vect.x < min)
		vect.x = min;
	else if (vect.x > max)
		vect.x = max;
	if (vect.y < min)
		vect.y = min;
	else if (vect.y > max)
		vect.y = max;
	if (vect.z < min)
		vect.z = min;
	else if (vect.z > max)
		vect.z = max;
	return (vect);
}

t_vect	get_random_uvect(uint32_t *state)
{
	t_vect	res;
	float	a;
	float	r;

	a = fast_rand(state) * 2.0 * M_PI;
	res.z = (fast_rand(state) * 2.0) - 1.0;
	r = sqrtf(1.0 - (res.z * res.z));
	res.x = r * cosf(a);
	res.y = r * sinf(a);
	return (res);
}

/*
t_vect	get_random_uvect(uint32_t *state)
{
	t_vect	res;
	float	bound;

	while (1)
	{
		res.x = (fast_rand(state) - 0.5) * 2;
		res.y = (fast_rand(state) - 0.5) * 2;
		res.z = (fast_rand(state) - 0.5) * 2;
		bound = vect_dot(res, res);
		if (1e-40 < bound && bound <= 1)
		{
			res = vect_simple_div(res, sqrtf(bound));
			return (res);
		}
	}
}*/

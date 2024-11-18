/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:09:48 by vperez-f          #+#    #+#             */
/*   Updated: 2024/11/18 14:19:52 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vect		new_color(float v1, float v2, float v3)
{
	t_vect	vect;

	vect.x = v1;
	vect.y = v2;
	vect.z = v3;
	return (vect);
}

t_coords	new_coords(float v1, float v2, float v3)
{
	t_coords	coord;

	coord.x = v1;
	coord.y = v2;
	coord.z = v3;
	return (coord);
}
t_vect	new_vect(float v1, float v2, float v3)
{
	t_vect	vect;

	vect.x = v1;
	vect.y = v2;
	vect.z = v3;
	return (vect);
}

t_ray	new_ray(t_vect dir, t_vect origin)
{
	t_ray	res;

	res.dir.x = dir.x;
	res.dir.y = dir.y;
	res.dir.z = dir.z;
	res.origin.x = origin.x;
	res.origin.y = origin.y;
	res.origin.z = origin.z;
	return (res);
}

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

t_vect	ray_at(t_ray ray, float pos)
{
	t_vect	res;

	res = vect_add(ray.origin,(vect_simple_mult(ray.dir, pos)));
	return (res);
}

t_vect	vect_simple_div(t_vect vec, float num)
{
	t_vect res;

	res.x = vec.x / num;
	res.y = vec.y / num;
	res.z = vec.z / num;
	return (res);
}

t_vect	vect_simple_mult(t_vect vec, float num)
{
	t_vect res;

	res.x = vec.x * num;
	res.y = vec.y * num;
	res.z = vec.z * num;
	return (res);
}

t_vect	vect_simple_subtract(t_vect vec, float num)
{
	t_vect res;

	res.x = vec.x - num;
	res.y = vec.y - num;
	res.z = vec.z - num;
	return (res);
}

t_vect	vect_simple_add(t_vect vec, float num)
{
	t_vect res;

	res.x = vec.x + num;
	res.y = vec.y + num;
	res.z = vec.z + num;
	return (res);
}

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

float	vect_dot(t_vect vec, t_vect vec2)
{
	return ((vec.x * vec2.x) + (vec.y * vec2.y) + (vec.z * vec2.z));
}

t_vect	vect_cross(t_vect vec, t_vect vec2)
{
	t_vect res;

	res.x = (vec.y * vec2.z) - (vec.z * vec2.y);
	res.y = (vec.z * vec2.x) - (vec.x * vec2.z);
	res.z = (vec.x * vec2.y) - (vec.y * vec2.x);
	return (res);
}

bool	zero_vect(t_vect vect)
{
	float	threshold;

	threshold = 1e-8;
	return ((fabsf(vect.x) < threshold) && (fabsf(vect.y) < threshold) && (fabsf(vect.z) < threshold));
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

float	vect_length(t_vect vec)
{
	return (sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}

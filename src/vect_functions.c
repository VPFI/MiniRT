/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:09:48 by vperez-f          #+#    #+#             */
/*   Updated: 2024/10/04 18:39:09 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vect	new_vect(float v1, float v2, float v3)
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

t_vect	vect_subtract(t_vect vec, t_vect vec2)
{
	t_vect res;

	res.x = vec.x + vec2.x;
	res.y = vec.y + vec2.y;
	res.z = vec.z + vec2.z;
	return (res);
}

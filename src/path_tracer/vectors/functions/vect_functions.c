/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:09:48 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 16:51:58 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

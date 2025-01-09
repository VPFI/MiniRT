/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:18:37 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 21:21:04 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:46:53 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:14:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"

t_vect	new_color(float v1, float v2, float v3)
{
	t_vect	vect;

	vect.x = v1;
	vect.y = v2;
	vect.z = v3;
	return (vect);
}

t_vect	new_vect(float v1, float v2, float v3)
{
	t_vect	vect;

	vect.x = v1;
	vect.y = v2;
	vect.z = v3;
	return (vect);
}

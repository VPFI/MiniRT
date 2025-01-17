/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:48:08 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/17 19:29:54 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

// Xorshift || https://en.wikipedia.org/wiki/Xorshift || [0,1]
float	fast_rand(uint32_t *state)
{
	*state ^= *state << 13;
	*state ^= *state >> 17;
	*state ^= *state << 5;
	return (*state / (float)UINT32_MAX);
}

float	f_clamp(float target, float min, float max)
{
	if (target < min)
		return (min);
	if (target > max)
		return (max);
	return (target);
}

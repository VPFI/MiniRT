/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:48:08 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 15:35:00 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Xorshift || https://en.wikipedia.org/wiki/Xorshift || [0,1]
float fast_rand(uint32_t *state)
{
	uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return (x / (float)UINT32_MAX);
}

float	f_clamp(float target, float min, float max)
{
	if (target < min)
		return (min);
	if (target > max)
		return (max);
	return (target);
}

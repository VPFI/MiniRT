/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:46:53 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 16:51:48 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_vect	new_color(float v1, float v2, float v3)
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

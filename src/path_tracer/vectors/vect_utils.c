/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:47:24 by vpf               #+#    #+#             */
/*   Updated: 2025/01/09 14:09:19 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_vect	get_random_uvect_alt(uint32_t *state)
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
}

int	vect_to_int(t_color color)
{
	return (get_rgba((int)(color.x * 255.9),
		(int)(color.y * 255.9), (int)(color.z * 255.9), 255));
}

t_color	hexa_to_vect(int color)
{
	t_color	res;

	res.x = get_r(color) / 255.0;
	res.y = get_g(color) / 255.0;
	res.z = get_b(color) / 255.0;
	return (res);
}
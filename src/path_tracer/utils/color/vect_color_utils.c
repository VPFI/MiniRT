/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_color_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:29:34 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 15:34:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

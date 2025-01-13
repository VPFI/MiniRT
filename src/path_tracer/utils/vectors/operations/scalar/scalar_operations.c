/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:42:37 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 16:44:58 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

float	vect_dot(t_vect vec, t_vect vec2)
{
	return ((vec.x * vec2.x) + (vec.y * vec2.y) + (vec.z * vec2.z));
}

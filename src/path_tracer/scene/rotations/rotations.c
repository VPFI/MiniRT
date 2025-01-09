/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:43:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/09 17:18:35 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//Euler-Rodrigues rotation formula  || https://en.wikipedia.org/wiki/Rodrigues_rotation_formula
void	rotate_vector(t_vect *vec, t_vect axis, float ang)
{
	t_vect		aux;
	float		cos;

	if (!ang)
		return ;
	aux = vect_cross(axis, *vec);
	cos = cosf(ang);
	*vec = vect_add(
		vect_add(vect_simple_mult(*vec, cos), vect_simple_mult(aux, sinf(ang))),
		vect_simple_mult(axis, vect_dot(*vec, axis) * (1 - cos)));
}

void	rotate_by_angle(t_vect *vect, t_vect *normal, float angle)
{
	t_vect	ideal;
	t_vect	axis;

	if (!angle)
		return ;
	ideal = new_vect(0.0, 0.0, 1.0);
	if (vect_dot(*normal, ideal) == -1.0)
		axis = new_vect(0.0, 1.0, 0.0);
	else
		axis = vect_cross(*normal, ideal);
	if (zero_vect(axis))
		return ;
	axis = unit_vect(axis);
	rotate_vector(vect, axis, angle);
}

float	rotate_reference_system(t_vect normal, t_vect *vec, t_vect *point)
{
	t_vect	axis;
	t_vect	ideal;
	float	angle;

	angle = 0.0;
	ideal = new_vect(0.0, 0.0, 1.0);
	if (vect_dot(normal, ideal) == -1.0)
		axis = new_vect(0.0, 1.0, 0.0);
	else
		axis = vect_cross(normal, ideal);
	if (zero_vect(axis))
		return (angle);
	axis = unit_vect(axis);
	angle = (acosf(f_clamp(vect_dot(normal, ideal), -1.0, 1.0)));
	if (vec && !zero_vect(*vec))
		rotate_vector(vec, axis, angle);
	if (point && !zero_vect(*point))
		rotate_vector(point, axis, angle);
	return (angle);	
}

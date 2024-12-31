/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:43:46 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 22:14:20 by vpf              ###   ########.fr       */
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

void	rotate_x(t_vect *pt, float angle)
{
	float	temp_y;
	float	temp_z;

	temp_y = pt->y;
	temp_z = pt->z;
	pt->y = (temp_y * cos(angle)) + (temp_z * (-sin(angle)));
	pt->z = (temp_y * sin(angle)) + (temp_z * cos(angle));
}

void	rotate_y(t_vect *pt, float angle)
{
	float	temp_x;
	float	temp_z;

	temp_x = pt->x;
	temp_z = pt->z;
	pt->x = (temp_x * cos(angle)) + (temp_z * sin(angle));
	pt->z = (temp_x * (-sin(angle))) + (temp_z * cos(angle));
}

void	rotate_z(t_vect *pt, float angle)
{
	float	temp_x;
	float	temp_y;

	temp_x = pt->x;
	temp_y = pt->y;
	pt->x = (temp_x * cos(angle)) + (temp_y * (-sin(angle)));
	pt->y = (temp_x * sin(angle)) + (temp_y * cos(angle));
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
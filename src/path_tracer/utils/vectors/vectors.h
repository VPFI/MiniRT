/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:59:07 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 17:21:53 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <stdint.h>
# include <stdbool.h>

typedef struct s_vect	t_color;

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}			t_vect;

t_vect	new_vect(float v1, float v2, float v3);
t_vect	new_color(float v1, float v2, float v3);

t_vect	unit_vect(t_vect vect);
bool	zero_vect(t_vect vect);
float	vect_length(t_vect vec);
t_vect	clamp_vect( t_vect vect, float min, float max);
t_vect	get_random_uvect(uint32_t *state);

t_vect	vect_simple_div(t_vect vec, float num);
t_vect	vect_simple_mult(t_vect vec, float num);
t_vect	vect_simple_subtract(t_vect vec, float num);
t_vect	vect_simple_add(t_vect vec, float num);
float	vect_dot(t_vect vec, t_vect vec2);

t_vect	vect_add(t_vect vec, t_vect vec2);
t_vect	vect_div(t_vect vec, t_vect vec2);
t_vect	vect_mult(t_vect vec, t_vect vec2);
t_vect	vect_cross(t_vect vec, t_vect vec2);
t_vect	vect_subtract(t_vect vec, t_vect vec2);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:23:09 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 14:49:02 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/scene/objects/objects.h"

typedef struct s_eq_params
{
	float	a;
	float	b;
	float	c;
	float	discr;
	float	root;
}			t_eq_params;

typedef struct s_pattern_vars
{
	int		x_index_square;
	int		y_index_square;
	int		pattern_index;
}			t_pattern_vars;

typedef struct s_base_params
{
	float 	point_arc;
	float	base_height;
	float	point_radius;
	t_vect	point_to_base;
}			t_base_params;

float	get_point_angle(t_vect *point);
float	get_vector_arc_height(t_vect *point);
t_vect	get_rotated_point_quad(t_hit_info *hit_info);

#endif
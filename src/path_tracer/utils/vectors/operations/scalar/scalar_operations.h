/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_operations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:52:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 22:01:46 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALAR_OPERATIONS_H
# define SCALAR_OPERATIONS_H

# include "path_tracer/utils/vectors/vectors.h"

float	vect_dot(t_vect vec, t_vect vec2);
t_vect	vect_simple_div(t_vect vec, float num);
t_vect	vect_simple_add(t_vect vec, float num);
t_vect	vect_simple_mult(t_vect vec, float num);
t_vect	vect_simple_subtract(t_vect vec, float num);

#endif
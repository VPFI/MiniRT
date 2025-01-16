/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:43:03 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 22:02:20 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_OPERATIONS_H
# define VECTOR_OPERATIONS_H

# include "path_tracer/utils/vectors/vectors.h"

t_vect	vect_add(t_vect vec, t_vect vec2);
t_vect	vect_div(t_vect vec, t_vect vec2);
t_vect	vect_mult(t_vect vec, t_vect vec2);
t_vect	vect_cross(t_vect vec, t_vect vec2);
t_vect	vect_subtract(t_vect vec, t_vect vec2);

#endif
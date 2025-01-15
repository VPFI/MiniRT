/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:23:09 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 21:39:19 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "src/path_tracer/utils/vectors/vectors.h"

float	get_point_angle(t_vect *point);
float	get_vector_arc_height(t_vect *point);

#endif
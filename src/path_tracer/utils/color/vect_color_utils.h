/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_color_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:39:58 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 22:29:44 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT_COLOR_UTILS_H
# define VECT_COLOR_UTILS_H

# include "src/path_tracer/vectors/vectors.h"

int		vect_to_int(t_color color);
t_color	hexa_to_vect(int color);

#endif
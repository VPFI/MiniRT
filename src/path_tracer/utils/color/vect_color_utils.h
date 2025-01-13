/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_color_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:39:58 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/11 22:57:58 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT_COLOR_UTILS_H
# define VECT_COLOR_UTILS_H

# include "src/path_tracer/utils/vectors/vectors.h"

int		vect_to_int(t_color color);
t_color	hexa_to_vect(int color);

#endif
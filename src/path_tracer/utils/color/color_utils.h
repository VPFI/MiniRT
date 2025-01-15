/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:32:56 by vpf               #+#    #+#             */
/*   Updated: 2025/01/14 19:35:20 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_UTILS_H
# define COLOR_UTILS_H

# include "src/path_tracer/utils/vectors/vectors.h"

int		get_r(int rgba);
int		get_g(int rgba);
int		get_b(int rgba);
int		get_a(int rgba);
int		get_rgba(int r, int g, int b, int a);

int		vect_to_int(t_color color);
t_color	hexa_to_vect(int color);

#endif
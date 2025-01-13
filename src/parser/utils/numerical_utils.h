/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numerical_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:02:36 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/11 22:57:58 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICAL_UTILS_H
# define NUMERICAL_UTILS_H

# include "src/path_tracer/utils/vectors/vectors.h"

void	check_bounds(float num, float min, float max);
float	ft_atof(char *array, float min, float max);
t_vect	input_to_vect(char *input, float min, float max);

#endif
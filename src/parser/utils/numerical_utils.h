/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numerical_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:02:36 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 22:33:04 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICAL_UTILS_H
# define NUMERICAL_UTILS_H

# include "src/path_tracer/vectors/vectors.h"

void	check_bounds(float num, float min, float max);
float	ft_atof(char *array, float min, float max);
t_vect	input_to_vect(char *input, float min, float max);

#endif
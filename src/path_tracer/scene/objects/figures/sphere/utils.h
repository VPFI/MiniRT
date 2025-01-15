/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:50 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/14 22:13:33 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/scene/objects/figures/figures.h"

typedef enum e_polar
{
	LONGITUDE = 0,
	LATITUDE = 1,
}			t_polar;

void	set_polar_coords(t_vect *point, t_figure *fig, float *polar_coords);

#endif
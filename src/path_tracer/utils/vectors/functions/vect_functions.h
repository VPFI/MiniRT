/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:52:36 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 21:59:52 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT_FUNCTIONS_H
# define VECT_FUNCTIONS_H

# include "path_tracer/utils/vectors/vectors.h"

t_vect	unit_vect(t_vect vect);
bool	zero_vect(t_vect vect);
float	vect_length(t_vect vec);
t_vect	get_random_uvect(uint32_t *state);
t_vect	clamp_vect( t_vect vect, float min, float max);

#endif
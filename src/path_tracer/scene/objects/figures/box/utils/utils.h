/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:50 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 20:11:20 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/scene/objects/objects.h"
# include "path_tracer/scene/objects/figures/figures.h"
# include "path_tracer/scene/objects/material/material.h"

void	add_box_face(t_object *box, t_figure face, t_material mat);
int		correct_box_pattern_index(t_vect *dimensions,
			int face_index, int pattern_index);

#endif